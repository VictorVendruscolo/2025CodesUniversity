#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_NODES 1000050
#define END_OF_LIST 0xFFFFFFFF

typedef struct {
    unsigned int value;
    unsigned int next;
} Node;

Node pool[MAX_NODES];
volatile unsigned char bitmap[MAX_NODES];

volatile int items_for_t1 = 0;
volatile int items_for_t2 = 0;
volatile int items_for_t3 = 0;

volatile int t0_done = 0;
volatile int t1_done = 0;
volatile int t2_done = 0;

unsigned int dummy_head;

unsigned int allocate_node() {
    static unsigned int last_alloc = 0;
    for (unsigned int i = 0; i < MAX_NODES; i++) {
        unsigned int idx = (last_alloc + i) % MAX_NODES;
        if (bitmap[idx] == 0) {
            bitmap[idx] = 1;
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

void* t1_evens(void* arg) {
    unsigned int prev = dummy_head;
    unsigned int pending_t1 = END_OF_LIST; 

    while (1) {
        while (items_for_t1 == 0 && !t0_done) { }
        if (items_for_t1 == 0 && t0_done) break;

        __sync_fetch_and_sub(&items_for_t1, 1);

        unsigned int curr;
        while ((curr = pool[prev].next) == END_OF_LIST) { }

        unsigned int val = pool[curr].value;
        if (val > 2 && val % 2 == 0) {
            pool[prev].next = pool[curr].next;
            bitmap[curr] = 0;
        } else {
            prev = curr;
            if (pending_t1 != END_OF_LIST) {
                __sync_fetch_and_add(&items_for_t2, 1);
            }
            pending_t1 = curr;
        }
    }
    if (pending_t1 != END_OF_LIST) {
        __sync_fetch_and_add(&items_for_t2, 1);
    }
    t1_done = 1;
    return NULL;
}

void* t2_primes(void* arg) {
    unsigned int prev = dummy_head;
    unsigned int pending_t2 = END_OF_LIST;

    while (1) {
        while (items_for_t2 == 0 && !t1_done) { }
        if (items_for_t2 == 0 && t1_done) break;

        __sync_fetch_and_sub(&items_for_t2, 1);

        unsigned int curr;
        while ((curr = pool[prev].next) == END_OF_LIST) { }

        unsigned int val = pool[curr].value;
        if (!is_prime(val)) {
            pool[prev].next = pool[curr].next;
            bitmap[curr] = 0;
        } else {
            prev = curr;
            if (pending_t2 != END_OF_LIST) {
                __sync_fetch_and_add(&items_for_t3, 1);
            }
            pending_t2 = curr;
        }
    }
    if (pending_t2 != END_OF_LIST) {
        __sync_fetch_and_add(&items_for_t3, 1);
    }
    t2_done = 1;
    return NULL;
}

void* t3_print(void* arg) {
    unsigned int prev = dummy_head;
    
    // Abre o ficheiro out.txt para escrita
    FILE *out_f = fopen("out.txt", "w");
    if (!out_f) return NULL;

    while (1) {
        while (items_for_t3 == 0 && !t2_done) { }
        if (items_for_t3 == 0 && t2_done) break;

        __sync_fetch_and_sub(&items_for_t3, 1);

        unsigned int curr;
        while ((curr = pool[prev].next) == END_OF_LIST) { }

        // Escreve diretamente no ficheiro out.txt
        fprintf(out_f, "%u ", pool[curr].value);
        fflush(out_f); // Garante a descarga imediata para o disco

        prev = curr;
    }
    
    fclose(out_f); // Fecha o ficheiro com segurança antes de terminar
    return NULL;
}

int main() {
    for (unsigned int i = 0; i < MAX_NODES; i++) {
        bitmap[i] = 0;
    }

    dummy_head = allocate_node();
    pool[dummy_head].value = 0;
    pool[dummy_head].next = END_OF_LIST;

    pthread_t t1, t2, t3;
    pthread_create(&t1, NULL, t1_evens, NULL);
    pthread_create(&t2, NULL, t2_primes, NULL);
    pthread_create(&t3, NULL, t3_print, NULL);

    FILE *f = fopen("in.txt", "r"); //lê arquivo "in.txt" do diretório atual
    if (!f) return 1;

    unsigned int tail = dummy_head;
    unsigned int val;
    unsigned int pending_t0 = END_OF_LIST;

    while (fscanf(f, "%u", &val) == 1) {
        unsigned int new_node = allocate_node();
        pool[new_node].value = val;
        pool[new_node].next = END_OF_LIST;

        pool[tail].next = new_node;
        tail = new_node;

        if (pending_t0 != END_OF_LIST) {
            __sync_fetch_and_add(&items_for_t1, 1);
        }
        pending_t0 = new_node;
    }
    fclose(f);

    if (pending_t0 != END_OF_LIST) {
        __sync_fetch_and_add(&items_for_t1, 1);
    }
    t0_done = 1;

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    
    return 0;
}