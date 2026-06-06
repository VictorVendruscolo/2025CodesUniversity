#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_NODES 1000050
#define END_OF_LIST 0xFFFFFFFF
#define SHM_NAME "/trabalho2_so_shm"

typedef struct {
    unsigned int value;
    unsigned int next;
} Node;

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

int is_prime(unsigned int n) {
    if (n <= 1) return 0;
    if (n == 2 || n == 3) return 1;
    if (n % 2 == 0 || n % 3 == 0) return 0;
    for (unsigned int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return 0;
    }
    return 1;
}

void process_p1(SharedMem* shm) {
    unsigned int prev = shm->dummy_head;
    unsigned int pending_p1 = END_OF_LIST;
    
    while (1) {
        while (shm->items_for_p1 == 0 && !shm->p0_done) { }
        if (shm->items_for_p1 == 0 && shm->p0_done) break;

        __sync_fetch_and_sub(&shm->items_for_p1, 1);

        unsigned int curr;
        while ((curr = shm->pool[prev].next) == END_OF_LIST) { }

        unsigned int val = shm->pool[curr].value;
        if (val > 2 && val % 2 == 0) {
            shm->pool[prev].next = shm->pool[curr].next;
            shm->bitmap[curr] = 0;
        } else {
            prev = curr;
            if (pending_p1 != END_OF_LIST) {
                __sync_fetch_and_add(&shm->items_for_p2, 1);
            }
            pending_p1 = curr;
        }
    }
    if (pending_p1 != END_OF_LIST) {
        __sync_fetch_and_add(&shm->items_for_p2, 1);
    }
    shm->p1_done = 1;
    exit(0);
}

void process_p2(SharedMem* shm) {
    unsigned int prev = shm->dummy_head;
    unsigned int pending_p2 = END_OF_LIST;
    
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
            if (pending_p2 != END_OF_LIST) {
                __sync_fetch_and_add(&shm->items_for_p3, 1);
            }
            pending_p2 = curr;
        }
    }
    if (pending_p2 != END_OF_LIST) {
        __sync_fetch_and_add(&shm->items_for_p3, 1);
    }
    shm->p2_done = 1;
    exit(0);
}

void process_p3(SharedMem* shm) {
    unsigned int prev = shm->dummy_head;
    
    // Abre o ficheiro out.txt para escrita no espaço do processo filho
    FILE *out_f = fopen("out.txt", "w");
    if (!out_f) exit(1);

    while (1) {
        while (shm->items_for_p3 == 0 && !shm->p2_done) { }
        if (shm->items_for_p3 == 0 && shm->p2_done) break;

        __sync_fetch_and_sub(&shm->items_for_p3, 1);

        unsigned int curr;
        while ((curr = shm->pool[prev].next) == END_OF_LIST) { }

        // Escreve diretamente no ficheiro out.txt
        fprintf(out_f, "%u ", shm->pool[curr].value);
        fflush(out_f);

        prev = curr;
    }
    
    fclose(out_f); // Fecha o ficheiro com segurança antes do exit
    exit(0);
}

int main() {
    shm_unlink(SHM_NAME);

    int shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0600);
    if (shm_fd < 0) return 1;

    if (ftruncate(shm_fd, sizeof(SharedMem)) == -1) return 1;

    SharedMem* shm = mmap(0, sizeof(SharedMem), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (shm == MAP_FAILED) return 1;

    memset(shm, 0, sizeof(SharedMem));
    shm->dummy_head = allocate_node(shm);
    shm->pool[shm->dummy_head].value = 0;
    shm->pool[shm->dummy_head].next = END_OF_LIST;

    pid_t p1 = fork();
    if (p1 == 0) process_p1(shm);

    pid_t p2 = fork();
    if (p2 == 0) process_p2(shm);

    pid_t p3 = fork();
    if (p3 == 0) process_p3(shm);

    FILE *f = fopen("in.txt", "r");
    if (!f) return 1;

    unsigned int tail = shm->dummy_head;
    unsigned int val;
    unsigned int pending_p0 = END_OF_LIST;

    while (fscanf(f, "%u", &val) == 1) {
        unsigned int new_node = allocate_node(shm);
        shm->pool[new_node].value = val;
        shm->pool[new_node].next = END_OF_LIST;

        shm->pool[tail].next = new_node;
        tail = new_node;

        if (pending_p0 != END_OF_LIST) {
            __sync_fetch_and_add(&shm->items_for_p1, 1);
        }
        pending_p0 = new_node;
    }
    fclose(f);

    if (pending_p0 != END_OF_LIST) {
        __sync_fetch_and_add(&shm->items_for_p1, 1);
    }
    shm->p0_done = 1;
    
    waitpid(p1, NULL, 0);
    waitpid(p2, NULL, 0);
    waitpid(p3, NULL, 0);

    munmap(shm, sizeof(SharedMem));
    shm_unlink(SHM_NAME);

    return 0;
}