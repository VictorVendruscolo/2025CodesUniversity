#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <string.h>

/* Tamanho do Buffer e Sentinela */
#define MAX_NODES 1000050
#define END_OF_LIST 0xFFFFFFFF
#define SHM_NAME "/trabalho2_so_shm"

/* Estrutura do Nó (Aritmética baseada em Offsets) */
typedef struct {
    unsigned int value;
    unsigned int next;
} Node;

/* ======================================================================
 * NÚCLEO DA MEMÓRIA PARTILHADA (IPC)
 * Todas as variáveis partilhadas devem residir aqui para serem visíveis 
 * por todos os processos após o fork().
 * ====================================================================== */
typedef struct {
    Node pool[MAX_NODES];
    volatile unsigned char bitmap[MAX_NODES]; 
    volatile int items_for_p1;
    volatile int items_for_p2;
    volatile int items_for_p3;
    volatile int p0_done;
    volatile int p1_done;
    volatile int p2_done;
    unsigned int dummy_head;
} SharedMem;

/* ======================================================================
 * GESTOR DE MEMÓRIA CUSTOMIZADO
 * ====================================================================== */
unsigned int allocate_node(SharedMem* shm) {
    static unsigned int last_alloc = 0;
    for (unsigned int i = 0; i < MAX_NODES; i++) {
        unsigned int idx = (last_alloc + i) % MAX_NODES;
        if (shm->bitmap[idx] == 0) {
            shm->bitmap[idx] = 1;
            last_alloc = (idx + 1) % MAX_NODES;
            return idx;
        }
    }
    return END_OF_LIST;
}

/* ======================================================================
 * LÓGICA MATEMÁTICA
 * ====================================================================== */
int is_prime(unsigned int n) {
    if (n <= 1) return 0;
    if (n == 2 || n == 3) return 1;
    if (n % 2 == 0 || n % 3 == 0) return 0;
    for (unsigned int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return 0;
    }
    return 1;
}

/* ======================================================================
 * PROCESSO FILHO 1: FILTRO DE PARES > 2
 * ====================================================================== */
void process_p1(SharedMem* shm) {
    unsigned int prev = shm->dummy_head;
    while (1) {
        // Barreira Lógica
        while (shm->items_for_p1 == 0 && !shm->p0_done) { }
        if (shm->items_for_p1 == 0 && shm->p0_done) break;

        __sync_fetch_and_sub(&shm->items_for_p1, 1);

        unsigned int curr;
        while ((curr = shm->pool[prev].next) == END_OF_LIST) { }

        unsigned int val = shm->pool[curr].value;
        if (val > 2 && val % 2 == 0) {
            // Remoção lógica
            shm->pool[prev].next = shm->pool[curr].next;
            // Desalocação
            shm->bitmap[curr] = 0;
        } else {
            // Avanço
            prev = curr;
            __sync_fetch_and_add(&shm->items_for_p2, 1);
        }
    }
    shm->p1_done = 1;
    exit(0); // O processo filho é destruído aqui
}

/* ======================================================================
 * PROCESSO FILHO 2: FILTRO DE PRÓXIMOS/NÃO PRIMOS
 * ====================================================================== */
void process_p2(SharedMem* shm) {
    unsigned int prev = shm->dummy_head;
    while (1) {
        while (shm->items_for_p2 == 0 && !shm->p1_done) { }
        if (shm->items_for_p2 == 0 && shm->p1_done) break;

        __sync_fetch_and_sub(&shm->items_for_p2, 1);

        unsigned int curr;
        while ((curr = shm->pool[prev].next) == END_OF_LIST) { }

        unsigned int val = shm->pool[curr].value;
        if (!is_prime(val)) {
            shm->pool[prev].next = shm->pool[curr].next;
            shm->bitmap[curr] = 0;
        } else {
            prev = curr;
            __sync_fetch_and_add(&shm->items_for_p3, 1);
        }
    }
    shm->p2_done = 1;
    exit(0);
}

/* ======================================================================
 * PROCESSO FILHO 3: CONSUMIDOR FINAL (IMPRESSÃO)
 * ====================================================================== */
void process_p3(SharedMem* shm) {
    unsigned int prev = shm->dummy_head;
    while (1) {
        while (shm->items_for_p3 == 0 && !shm->p2_done) { }
        if (shm->items_for_p3 == 0 && shm->p2_done) break;

        __sync_fetch_and_sub(&shm->items_for_p3, 1);

        unsigned int curr;
        while ((curr = shm->pool[prev].next) == END_OF_LIST) { }

        printf("%u\n", shm->pool[curr].value);
        fflush(stdout);

        prev = curr;
    }
    exit(0);
}

/* ======================================================================
 * FLUXO PRINCIPAL DO SISTEMA (PRODUTOR / PAI)
 * ====================================================================== */
int main() {
    // 1. Limpeza preventiva (caso uma execução anterior tenha crashado)
    shm_unlink(SHM_NAME);

    // 2. Criação do Objeto de Memória Partilhada POSIX
    int shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0600);
    if (shm_fd < 0) {
        perror("Erro Crítico: Falha na criação da Memória Partilhada");
        return 1;
    }

    // 3. Dimensionamento do Buffer (ftruncate)
    if (ftruncate(shm_fd, sizeof(SharedMem)) == -1) {
        perror("Erro Crítico: Falha no dimensionamento da IPC");
        return 1;
    }

    // 4. Mapeamento para o Espaço de Endereçamento do Pai (mmap)
    SharedMem* shm = mmap(0, sizeof(SharedMem), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (shm == MAP_FAILED) {
        perror("Erro Crítico: Falha no mmap");
        return 1;
    }

    // Inicialização da estrutura de controlo
    memset(shm, 0, sizeof(SharedMem));
    shm->dummy_head = allocate_node(shm);
    shm->pool[shm->dummy_head].value = 0;
    shm->pool[shm->dummy_head].next = END_OF_LIST;

    // 5. Clonagem Múltipla via fork()
    pid_t p1 = fork();
    if (p1 == 0) process_p1(shm); // Entra na rotina e morre (exit)

    pid_t p2 = fork();
    if (p2 == 0) process_p2(shm);

    pid_t p3 = fork();
    if (p3 == 0) process_p3(shm);

    // 6. Ingestão de Dados pelo Processo Pai (Fluxo Principal)
    FILE *f = fopen("in.txt", "r");
    if (!f) {
        perror("Erro Crítico: Ficheiro in.txt não encontrado.");
        return 1;
    }

    unsigned int tail = shm->dummy_head;
    unsigned int val;

    while (fscanf(f, "%u", &val) == 1) {
        unsigned int new_node = allocate_node(shm);
        if (new_node == END_OF_LIST) {
            fprintf(stderr, "Erro Crítico: Esgotamento do Mapa de Bits.\n");
            break;
        }

        shm->pool[new_node].value = val;
        shm->pool[new_node].next = END_OF_LIST;

        shm->pool[tail].next = new_node;
        tail = new_node;

        // Assinala atomicamente na memória partilhada o avanço produtivo
        __sync_fetch_and_add(&shm->items_for_p1, 1);
    }
    fclose(f);

    // 7. Desligamento Sistémico e Sincronização de Encerramento (waitpid)
    shm->p0_done = 1;
    
    // O Pai bloqueia até confirmar a morte de todos os processos filhos
    waitpid(p1, NULL, 0);
    waitpid(p2, NULL, 0);
    waitpid(p3, NULL, 0);

    // 8. Desalocação e Destruição Formal dos Recursos do SO
    munmap(shm, sizeof(SharedMem));
    shm_unlink(SHM_NAME); // Desvincula o bloco do Kernel

    return 0;
}