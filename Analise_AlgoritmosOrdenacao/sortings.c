/**
 * ALGORITMOS E ESTRUTURAS DE DADOS II
 * Trabalho Prático: Implementação e Análise de Algoritmos de Ordenação
 * 
 * Implementação de 8 algoritmos de ordenação:
 * 1. Bubble Sort Original
 * 2. Bubble Sort Melhorado
 * 3. Insertion Sort
 * 4. Mergesort
 * 5. Quicksort (pivô último elemento)
 * 6. Quicksort (pivô aleatório)
 * 7. Quicksort (mediana de três)
 * 8. Heapsort
 * 
 * Compilação: gcc -Wall -Wextra -pedantic -O2 -o sortings sortings.c -lm
 * Uso: ./sortings <1-8> <arquivo_entrada.bin> <arquivo_saida.bin>
 * 
 * Baseado nos slides Prof. Fabrício Sérgio de Paula - UEMS
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <sys/stat.h>
#include <string.h>

/* ========================================================================
 * FUNÇÕES AUXILIARES DE ENTRADA/SAÍDA
 * ======================================================================== */

int ler_arquivo_binario(const char* nome_arquivo, int32_t** vetor) {
    FILE* arquivo = fopen(nome_arquivo, "rb");
    if (!arquivo) {
        fprintf(stderr, "Erro: não foi possível abrir o arquivo '%s' para leitura\n", nome_arquivo);
        return -1;
    }
    
    struct stat st;
    if (fstat(fileno(arquivo), &st) != 0) {
        fprintf(stderr, "Erro: não foi possível obter informações do arquivo '%s'\n", nome_arquivo);
        fclose(arquivo);
        return -1;
    }
    
    int num_elementos = st.st_size / sizeof(int32_t);
    if (st.st_size % sizeof(int32_t) != 0) {
        fprintf(stderr, "Erro: tamanho do arquivo não é múltiplo de %zu bytes\n", sizeof(int32_t));
        fclose(arquivo);
        return -1;
    }
    
    if (num_elementos <= 0) {
        fprintf(stderr, "Erro: arquivo vazio ou inválido\n");
        fclose(arquivo);
        return -1;
    }
    
    *vetor = malloc(num_elementos * sizeof(int32_t));
    if (!*vetor) {
        fprintf(stderr, "Erro: falha na alocação de memória para %d elementos\n", num_elementos);
        fclose(arquivo);
        return -1;
    }
    
    size_t elementos_lidos = fread(*vetor, sizeof(int32_t), num_elementos, arquivo);
    if ((int)elementos_lidos != num_elementos) {
        fprintf(stderr, "Erro: falha na leitura do arquivo. Esperado: %d, Lido: %zu\n", 
                num_elementos, elementos_lidos);
        free(*vetor);
        *vetor = NULL;
        fclose(arquivo);
        return -1;
    }
    
    fclose(arquivo);
    return num_elementos;
}

int escrever_arquivo_binario(const char* nome_arquivo, int32_t* vetor, int num_elementos) {
    FILE* arquivo = fopen(nome_arquivo, "wb");
    if (!arquivo) {
        fprintf(stderr, "Erro: não foi possível abrir o arquivo '%s' para escrita\n", nome_arquivo);
        return -1;
    }
    
    size_t elementos_escritos = fwrite(vetor, sizeof(int32_t), num_elementos, arquivo);
    if ((int)elementos_escritos != num_elementos) {
        fprintf(stderr, "Erro: falha na escrita do arquivo. Esperado: %d, Escrito: %zu\n", 
                num_elementos, elementos_escritos);
        fclose(arquivo);
        return -1;
    }
    
    fclose(arquivo);
    return 0;
}

/* ========================================================================
 * ALGORITMOS DE ORDENAÇÃO O(n²)
 * ======================================================================== */

void bubble_sort_original(int32_t* V, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (V[j] > V[j + 1]) {
                int32_t temp = V[j];
                V[j] = V[j + 1];
                V[j + 1] = temp;
            }
        }
    }
}

void bubble_sort_melhorado(int32_t* V, int n) {
    int limite = n - 1;
    
    while (limite > 0) {
        int troca = 0;
        
        for (int j = 0; j < limite; j++) {
            if (V[j] > V[j + 1]) {
                int32_t temp = V[j];
                V[j] = V[j + 1];
                V[j + 1] = temp;
                troca = j;
            }
        }
        
        limite = troca;
    }
}

void insertion_sort(int32_t* V, int n) {
    for (int i = 1; i < n; i++) {
        int32_t temp = V[i];
        int j = i - 1;
        
        while (j >= 0 && V[j] > temp) {
            V[j + 1] = V[j];
            j--;
        }
        
        V[j + 1] = temp;
    }
}

/* ========================================================================
 * MERGESORT - ALGORITMO O(n log n)
 * ======================================================================== */

static int32_t* temp_array = NULL;

void intercalar(int32_t* V, int inicio, int meio, int fim) {
    int i = inicio, j = meio + 1, k = 0;
    
    while (i <= meio && j <= fim) {
        if (V[i] <= V[j]) {
            temp_array[k++] = V[i++];
        } else {
            temp_array[k++] = V[j++];
        }
    }
    
    while (i <= meio) {
        temp_array[k++] = V[i++];
    }
    
    while (j <= fim) {
        temp_array[k++] = V[j++];
    }
    
    for (i = inicio, k = 0; i <= fim; i++, k++) {
        V[i] = temp_array[k];
    }
}

void mergesort_recursivo(int32_t* V, int inicio, int fim) {
    if (inicio < fim) {
        int meio = (inicio + fim) / 2;
        
        mergesort_recursivo(V, inicio, meio);
        mergesort_recursivo(V, meio + 1, fim);
        intercalar(V, inicio, meio, fim);
    }
}

void mergesort(int32_t* V, int n) {
    if (n <= 1) return;
    
    temp_array = malloc(n * sizeof(int32_t));
    if (!temp_array) {
        fprintf(stderr, "Erro: falha na alocação de memória para Mergesort\n");
        exit(1);
    }
    
    mergesort_recursivo(V, 0, n - 1);
    
    free(temp_array);
    temp_array = NULL;
}

/* ========================================================================
 * QUICKSORT - TRÊS VARIANTES
 * ======================================================================== */

int particionar(int32_t* V, int inicio, int fim) {
    int32_t pivo = V[fim];
    int i = inicio - 1;
    
    for (int j = inicio; j < fim; j++) {
        if (V[j] <= pivo) {
            i++;
            int32_t temp = V[i];
            V[i] = V[j];
            V[j] = temp;
        }
    }
    
    int32_t temp = V[i + 1];
    V[i + 1] = V[fim];
    V[fim] = temp;
    
    return i + 1;
}

int mediana_de_tres(int32_t* V, int inicio, int fim) {
    int meio = (inicio + fim) / 2;
    
    if (V[inicio] > V[meio]) {
        int32_t temp = V[inicio];
        V[inicio] = V[meio];
        V[meio] = temp;
    }
    
    if (V[meio] > V[fim]) {
        int32_t temp = V[meio];
        V[meio] = V[fim];
        V[fim] = temp;
        
        if (V[inicio] > V[meio]) {
            temp = V[inicio];
            V[inicio] = V[meio];
            V[meio] = temp;
        }
    }
    
    return meio;
}

void quicksort_ultimo_recursivo(int32_t* V, int inicio, int fim) {
    if (inicio < fim) {
        int pivo_pos = particionar(V, inicio, fim);
        quicksort_ultimo_recursivo(V, inicio, pivo_pos - 1);
        quicksort_ultimo_recursivo(V, pivo_pos + 1, fim);
    }
}

void quicksort_ultimo(int32_t* V, int n) {
    if (n > 1) {
        quicksort_ultimo_recursivo(V, 0, n - 1);
    }
}

void quicksort_aleatorio_recursivo(int32_t* V, int inicio, int fim) {
    if (inicio < fim) {
        int pivo_aleatorio = inicio + rand() % (fim - inicio + 1);
        int32_t temp = V[pivo_aleatorio];
        V[pivo_aleatorio] = V[fim];
        V[fim] = temp;
        
        int pivo_pos = particionar(V, inicio, fim);
        quicksort_aleatorio_recursivo(V, inicio, pivo_pos - 1);
        quicksort_aleatorio_recursivo(V, pivo_pos + 1, fim);
    }
}

void quicksort_aleatorio(int32_t* V, int n) {
    if (n > 1) {
        quicksort_aleatorio_recursivo(V, 0, n - 1);
    }
}

void quicksort_mediana3_recursivo(int32_t* V, int inicio, int fim) {
    if (inicio < fim) {
        int mediana_pos = mediana_de_tres(V, inicio, fim);
        int32_t temp = V[mediana_pos];
        V[mediana_pos] = V[fim];
        V[fim] = temp;
        
        int pivo_pos = particionar(V, inicio, fim);
        quicksort_mediana3_recursivo(V, inicio, pivo_pos - 1);
        quicksort_mediana3_recursivo(V, pivo_pos + 1, fim);
    }
}

void quicksort_mediana3(int32_t* V, int n) {
    if (n > 1) {
        quicksort_mediana3_recursivo(V, 0, n - 1);
    }
}

/* ========================================================================
 * HEAPSORT - ALGORITMO O(n log n)
 * ======================================================================== */

void descer(int32_t* V, int n, int i) {
    int maior = i;
    int esquerdo = 2 * i + 1;
    int direito = 2 * i + 2;
    
    if (esquerdo < n && V[esquerdo] > V[maior]) {
        maior = esquerdo;
    }
    
    if (direito < n && V[direito] > V[maior]) {
        maior = direito;
    }
    
    if (maior != i) {
        int32_t temp = V[i];
        V[i] = V[maior];
        V[maior] = temp;
        
        descer(V, n, maior);
    }
}

void construir_heap(int32_t* V, int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        descer(V, n, i);
    }
}

void heapsort(int32_t* V, int n) {
    if (n <= 1) return;
    
    construir_heap(V, n);
    
    for (int i = n - 1; i > 0; i--) {
        int32_t temp = V[0];
        V[0] = V[i];
        V[i] = temp;
        
        descer(V, i, 0);
    }
}

/* ========================================================================
 * FUNÇÃO MAIN
 * ======================================================================== */

void imprimir_ajuda(const char* nome_programa) {
    fprintf(stderr, "ALGORITMOS DE ORDENAÇÃO - TRABALHO PRÁTICO AEDII\n\n");
    fprintf(stderr, "Uso: %s <algoritmo> <arquivo_entrada.bin> <arquivo_saida.bin>\n\n", nome_programa);
    fprintf(stderr, "Algoritmos disponíveis:\n");
    fprintf(stderr, "  1 - Bubble Sort Original        (O(n²) sempre)\n");
    fprintf(stderr, "  2 - Bubble Sort Melhorado       (O(n) melhor, O(n²) pior)\n");
    fprintf(stderr, "  3 - Insertion Sort               (O(n) melhor, O(n²) pior)\n");
    fprintf(stderr, "  4 - Mergesort                    (O(n log n) sempre)\n");
    fprintf(stderr, "  5 - Quicksort (pivô último)      (O(n log n) médio, O(n²) pior)\n");
    fprintf(stderr, "  6 - Quicksort (pivô aleatório)   (O(n log n) esperado)\n");
    fprintf(stderr, "  7 - Quicksort (mediana de 3)     (O(n log n) médio otimizado)\n");
    fprintf(stderr, "  8 - Heapsort                     (O(n log n) sempre)\n\n");
    fprintf(stderr, "Exemplo: %s 4 entrada.bin saida.bin\n", nome_programa);
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        imprimir_ajuda(argv[0]);
        return 1;
    }
    
    int algoritmo = atoi(argv[1]);
    if (algoritmo < 1 || algoritmo > 8) {
        fprintf(stderr, "Erro: algoritmo deve ser um número entre 1 e 8\n\n");
        imprimir_ajuda(argv[0]);
        return 1;
    }
    
    int32_t* vetor = NULL;
    int num_elementos = ler_arquivo_binario(argv[2], &vetor);
    if (num_elementos == -1) {
        return 1;
    }
    
    if (algoritmo == 6) {
        srand(time(NULL));
    }
    
    struct timespec tempo_inicio, tempo_fim;
    clock_gettime(CLOCK_MONOTONIC, &tempo_inicio);
    
    switch (algoritmo) {
        case 1: bubble_sort_original(vetor, num_elementos); break;
        case 2: bubble_sort_melhorado(vetor, num_elementos); break;
        case 3: insertion_sort(vetor, num_elementos); break;
        case 4: mergesort(vetor, num_elementos); break;
        case 5: quicksort_ultimo(vetor, num_elementos); break;
        case 6: quicksort_aleatorio(vetor, num_elementos); break;
        case 7: quicksort_mediana3(vetor, num_elementos); break;
        case 8: heapsort(vetor, num_elementos); break;
        default:
            fprintf(stderr, "Erro interno: algoritmo inválido\n");
            free(vetor);
            return 1;
    }
    
    clock_gettime(CLOCK_MONOTONIC, &tempo_fim);
    
    double tempo_execucao = (tempo_fim.tv_sec - tempo_inicio.tv_sec) + 
                           (tempo_fim.tv_nsec - tempo_inicio.tv_nsec) / 1e9;
    
    if (escrever_arquivo_binario(argv[3], vetor, num_elementos) == -1) {
        free(vetor);
        return 1;
    }
    
    printf("%.3f\n", tempo_execucao);
    
    free(vetor);
    return 0;
}