#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

/* Tamanho máximo para acomodar 1 milhão de registos com margem de segurança */
#define MAX_NODES 1000050 
/* Sentinela exigido pela Spec (max_unsigned) */
#define END_OF_LIST 0xFFFFFFFF 

/* Estrutura do Nó com endereçamento relativo */
typedef struct {
    unsigned int value;
    unsigned int next; // Atua como um offset (índice), não como um ponteiro real
} Node;

/* Memória Partilhada entre as Threads */
Node pool[MAX_NODES];
volatile unsigned char bitmap[MAX_NODES]; // 0 = Livre, 1 = Ocupado

/* Variáveis Contadoras Compartilhadas (Lógica de Sinalização/Pipeline) */
volatile int items_for_t1 = 0;
volatile int items_for_t2 = 0;
volatile int items_for_t3 = 0;

/* Flags de término */
volatile int t0_done = 0;
volatile int t1_done = 0;
volatile int t2_done = 0;

/* Ponteiro (relativo) para a cabeça fictícia da lista */
unsigned int dummy_head;

/* ======================================================================
 * GESTOR DE MEMÓRIA CUSTOMIZADO (MEU MALLOC)
 * ====================================================================== */
unsigned int allocate_node() {
    static unsigned int last_alloc = 0;
    // Percorre circularmente o bitmap para garantir que demorará 
    // imenso tempo até tentar reaproveitar um bloco (evita ABA problem)
    for (unsigned int i = 0; i < MAX_NODES; i++) {
        unsigned int idx = (last_alloc + i) % MAX_NODES;
        if (bitmap[idx] == 0) {
            bitmap[idx] = 1; // Marca como ocupado
            last_alloc = (idx + 1) % MAX_NODES;
            return idx;
        }
    }
    return END_OF_LIST; // Buffer cheio
}

/* ======================================================================
 * LÓGICA MATEMÁTICA
 * ====================================================================== */
int is_prime(unsigned int n) {
    if (n <= 1) return 0;
    if (n == 2 || n == 3) return 1;
    if (n % 2 == 0 || n % 3 == 0) return 0;
    // Teste até à raiz quadrada de n (conforme spec)
    for (unsigned int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return 0;
    }
    return 1;
}

/* ======================================================================
 * FILTRO 1: REMOVE PARES > 2
 * ====================================================================== */
void* t1_evens(void* arg) {
    unsigned int prev = dummy_head;

    while (1) {
        // Barreira Lógica: Aguarda que o produtor indique disponibilidade
        while (items_for_t1 == 0 && !t0_done) { /* Busy wait para concorrência crua */ }
        if (items_for_t1 == 0 && t0_done) break;

        // Consome logicamente 1 item através de instrução atómica sem semáforos
        __sync_fetch_and_sub(&items_for_t1, 1);

        unsigned int curr;
        // Aguarda a ligação física do nó no offset
        while ((curr = pool[prev].next) == END_OF_LIST) { }

        unsigned int val = pool[curr].value;
        if (val > 2 && val % 2 == 0) {
            // Remoção lógica da lista
            pool[prev].next = pool[curr].next;
            // Desalocação local (responsabilidade de quem remove)
            bitmap[curr] = 0; 
        } else {
            // Mantém e avança na lista
            prev = curr;
            // Sinaliza para a T2 que há 1 novo item verificado
            __sync_fetch_and_add(&items_for_t2, 1);
        }
    }
    t1_done = 1;
    return NULL;
}

/* ======================================================================
 * FILTRO 2: REMOVE NÃO PRIMOS
 * ====================================================================== */
void* t2_primes(void* arg) {
    unsigned int prev = dummy_head;

    while (1) {
        // Aguarda disponibilidade por parte da T1
        while (items_for_t2 == 0 && !t1_done) { }
        if (items_for_t2 == 0 && t1_done) break;

        __sync_fetch_and_sub(&items_for_t2, 1);

        unsigned int curr;
        while ((curr = pool[prev].next) == END_OF_LIST) { }

        unsigned int val = pool[curr].value;
        if (!is_prime(val)) {
            // Remoção e desalocação
            pool[prev].next = pool[curr].next;
            bitmap[curr] = 0;
        } else {
            // Mantém e avança
            prev = curr;
            // Sinaliza para a T3 (Impressão)
            __sync_fetch_and_add(&items_for_t3, 1);
        }
    }
    t2_done = 1;
    return NULL;
}

/* ======================================================================
 * FILTRO 3 / CONSUMIDOR FINAL: IMPRESSÃO
 * ====================================================================== */
void* t3_print(void* arg) {
    unsigned int prev = dummy_head;

    while (1) {
        // Aguarda disponibilidade por parte da T2
        while (items_for_t3 == 0 && !t2_done) { }
        if (items_for_t3 == 0 && t2_done) break;

        __sync_fetch_and_sub(&items_for_t3, 1);

        unsigned int curr;
        while ((curr = pool[prev].next) == END_OF_LIST) { }

        // Impressão e descarga obrigatória do buffer concorrente
        printf("%u\n", pool[curr].value);
        fflush(stdout);

        prev = curr;
    }
    return NULL;
}

/* ======================================================================
 * FLUXO PRINCIPAL (PRODUTOR)
 * ====================================================================== */
int main() {
    // 1. Inicializa Mapa de Bits (0 = livre)
    for (unsigned int i = 0; i < MAX_NODES; i++) {
        bitmap[i] = 0;
    }

    // 2. Cria o Nó Cabeça Fictício (Dummy Head)
    dummy_head = allocate_node();
    pool[dummy_head].value = 0;
    pool[dummy_head].next = END_OF_LIST;

    // 3. Inicializa as Threads Adicionais Simultâneas
    pthread_t t1, t2, t3;
    pthread_create(&t1, NULL, t1_evens, NULL);
    pthread_create(&t2, NULL, t2_primes, NULL);
    pthread_create(&t3, NULL, t3_print, NULL);

    // 4. Ingestão de Dados do Ficheiro
    FILE *f = fopen("in.txt", "r");
    if (!f) {
        perror("Erro Crítico: Nao foi possivel abrir o ficheiro in.txt");
        return 1;
    }

    unsigned int tail = dummy_head;
    unsigned int val;

    while (fscanf(f, "%u", &val) == 1) {
        unsigned int new_node = allocate_node();
        if (new_node == END_OF_LIST) {
            fprintf(stderr, "Erro Crítico: Esgotamento do Mapa de Bits.\n");
            break;
        }

        // Construção segura (atribui o sentinela max_unsigned antes de ligar a lista)
        pool[new_node].value = val;
        pool[new_node].next = END_OF_LIST;

        // Anexa ao final da lista de endereços relativos
        pool[tail].next = new_node;
        tail = new_node;

        // Notifica a T1 através de variável contadora
        __sync_fetch_and_add(&items_for_t1, 1);
    }
    fclose(f);

    // 5. Sinaliza encerramento de ingestão e espera a linha de montagem esvaziar
    t0_done = 1;
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    return 0;
}