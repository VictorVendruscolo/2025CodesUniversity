#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ESTADOS 50
#define MAX_SIMBOLOS 10
#define MAX_TRANSICOES 100
#define MAX_LEN 30
#define TAM_LINHA_INPUT 256

// Estrutura para uma transição do AFN
typedef struct {
    char origem[MAX_LEN];
    char simbolo[MAX_LEN];
    char destino[MAX_LEN];
} TransicaoNFA;

// Estrutura para um estado do AFD
typedef struct {
    char nome;
    int num_estados_nfa;
    char estados_nfa[MAX_ESTADOS][MAX_LEN];
    int eh_final;
} EstadoDFA;

// Estrutura para uma transição do AFD
typedef struct {
    char origem_nome;
    char simbolo[MAX_LEN];
    char destino_nome;
} TransicaoDFA;


// --- Funções Utilitárias ---

// Leitura segura de string, agora usando size_t para evitar warnings
void getsCustom(char *str, int t) {
    if (fgets(str, t, stdin) == NULL) { // (FIX) Adicionada verificação de retorno
        str[0] = '\0';
        return;
    }
    size_t tam = strlen(str); // (FIX) Usando size_t para o tipo de strlen
    if (tam > 0 && str[tam - 1] == '\n') {
        str[tam - 1] = '\0';
    }
}

// Divide string por espaço em uma matriz
void split(char M[MAX_ESTADOS][MAX_LEN], char *str, int *tam) {
    int i = 0;
    char *token = strtok(str, " \t\n");
    while (token != NULL && i < MAX_ESTADOS) {
        strcpy(M[i++], token);
        token = strtok(NULL, " \t\n");
    }
    *tam = i;
}

// Verifica se um elemento (string) pertence a um conjunto (matriz de strings)
int pertence(const char *el, char M[MAX_ESTADOS][MAX_LEN], int tam) {
    for (int i = 0; i < tam; i++) {
        if (strcmp(el, M[i]) == 0) return 1;
    }
    return 0;
}

// Ordena um conjunto de estados (strings) para comparação
void ordenar_conjunto_str(char M[MAX_ESTADOS][MAX_LEN], int tam) {
    char temp[MAX_LEN];
    for (int i = 0; i < tam - 1; i++) {
        for (int j = 0; j < tam - i - 1; j++) {
            if (strcmp(M[j], M[j + 1]) > 0) {
                strcpy(temp, M[j]);
                strcpy(M[j], M[j + 1]);
                strcpy(M[j + 1], temp);
            }
        }
    }
}

// Compara dois conjuntos de estados (strings). Retorna 1 se forem iguais.
int conjuntos_iguais_str(char M1[MAX_ESTADOS][MAX_LEN], int tam1, char M2[MAX_ESTADOS][MAX_LEN], int tam2) {
    if (tam1 != tam2) return 0;
    ordenar_conjunto_str(M1, tam1);
    ordenar_conjunto_str(M2, tam2);
    for (int i = 0; i < tam1; i++) {
        if (strcmp(M1[i], M2[i]) != 0) return 0;
    }
    return 1;
}

// --- Funções do Algoritmo ---

int fecho_epsilon(char T[MAX_ESTADOS][MAX_LEN], int tam_T, TransicaoNFA nfa_delta[], int num_trans_nfa, char resultado[MAX_ESTADOS][MAX_LEN]) {
    int tam_resultado = 0;
    char pilha[MAX_ESTADOS][MAX_LEN];
    int topo_pilha = 0;

    for (int i = 0; i < tam_T; i++) {
        strcpy(resultado[tam_resultado++], T[i]);
        strcpy(pilha[topo_pilha++], T[i]);
    }

    while (topo_pilha > 0) {
        char t[MAX_LEN];
        strcpy(t, pilha[--topo_pilha]);

        for (int i = 0; i < num_trans_nfa; i++) {
            if (strcmp(nfa_delta[i].origem, t) == 0 && strcmp(nfa_delta[i].simbolo, "&") == 0) {
                if (!pertence(nfa_delta[i].destino, resultado, tam_resultado)) {
                    strcpy(resultado[tam_resultado++], nfa_delta[i].destino);
                    strcpy(pilha[topo_pilha++], nfa_delta[i].destino);
                }
            }
        }
    }
    return tam_resultado;
}

int move(char T[MAX_ESTADOS][MAX_LEN], int tam_T, const char* simbolo, TransicaoNFA nfa_delta[], int num_trans_nfa, char resultado[MAX_ESTADOS][MAX_LEN]) {
    int tam_resultado = 0;
    for (int i = 0; i < tam_T; i++) {
        for (int j = 0; j < num_trans_nfa; j++) {
            if (strcmp(nfa_delta[j].origem, T[i]) == 0 && strcmp(nfa_delta[j].simbolo, simbolo) == 0) {
                if (!pertence(nfa_delta[j].destino, resultado, tam_resultado)) {
                    strcpy(resultado[tam_resultado++], nfa_delta[j].destino);
                }
            }
        }
    }
    return tam_resultado;
}


// --- Função Principal ---

int main() {
    char Q[MAX_ESTADOS][MAX_LEN], A[MAX_SIMBOLOS][MAX_LEN], F[MAX_ESTADOS][MAX_LEN], q0[MAX_LEN];
    char str_input[TAM_LINHA_INPUT];
    int tamA, tamF;
    // (FIX) Removida variável tamQ não utilizada para evitar warning.
    TransicaoNFA nfa_delta[MAX_TRANSICOES];
    int num_trans_nfa;

    char opcao;
    do {
        printf("\n& CONVERSOR DE AFN PARA AFD &\n");
        printf("----------------------------------\n");
        
        printf("Entre com os estados do AFN (ex: q0 q1 q2): ");
        getsCustom(str_input, sizeof(str_input));
        split(Q, str_input, &tamA); // A variável tamA será usada para Q temporariamente, mas não tem problema.

        printf("Entre com o alfabeto do AFN (ex: a b): ");
        getsCustom(str_input, sizeof(str_input));
        split(A, str_input, &tamA);

        printf("Entre com o estado inicial do AFN (ex: q0): ");
        getsCustom(q0, sizeof(q0));

        printf("Entre com os estados finais do AFN (ex: q2 q3): ");
        getsCustom(str_input, sizeof(str_input));
        split(F, str_input, &tamF);

        printf("\nInforme as transicoes do AFN (Origem Simbolo Destino).\n");
        printf("Use '&' para a palavra vazia. Pressione ENTER em uma linha vazia para finalizar.\n");
        num_trans_nfa = 0;
        while(num_trans_nfa < MAX_TRANSICOES){
            printf("  d_nfa > ");
            getsCustom(str_input, sizeof(str_input));
            if(strlen(str_input) == 0) break;

            char temp_orig[MAX_LEN], temp_symb[MAX_LEN], temp_dest[MAX_LEN];
            if(sscanf(str_input, "%s %s %s", temp_orig, temp_symb, temp_dest) == 3){
                strcpy(nfa_delta[num_trans_nfa].origem, temp_orig);
                strcpy(nfa_delta[num_trans_nfa].simbolo, temp_symb);
                strcpy(nfa_delta[num_trans_nfa].destino, temp_dest);
                num_trans_nfa++;
            } else {
                printf("    Formato invalido.\n");
            }
        }
        
        printf("\n...Iniciando conversao para AFD...\n");
        
        EstadoDFA dfa_states[MAX_ESTADOS];
        int num_dfa_states = 0;
        TransicaoDFA dfa_delta[MAX_TRANSICOES];
        int num_dfa_trans = 0;
        char proximo_nome_dfa = 'A';

        int fila_processamento[MAX_ESTADOS];
        int inicio_fila = 0, fim_fila = 0;

        char estado_inicial_nfa[1][MAX_LEN];
        strcpy(estado_inicial_nfa[0], q0);
        
        EstadoDFA q0_dfa;
        q0_dfa.nome = proximo_nome_dfa++;
        q0_dfa.num_estados_nfa = fecho_epsilon(estado_inicial_nfa, 1, nfa_delta, num_trans_nfa, q0_dfa.estados_nfa);
        
        dfa_states[num_dfa_states++] = q0_dfa;
        fila_processamento[fim_fila++] = 0;

        while(inicio_fila < fim_fila){
            int idx_T = fila_processamento[inicio_fila++];
            EstadoDFA T = dfa_states[idx_T];

            for(int i=0; i<tamA; i++){
                char simbolo_a[MAX_LEN];
                strcpy(simbolo_a, A[i]);

                char move_res[MAX_ESTADOS][MAX_LEN];
                int tam_move = move(T.estados_nfa, T.num_estados_nfa, simbolo_a, nfa_delta, num_trans_nfa, move_res);
                
                if(tam_move == 0) continue;

                char U_estados[MAX_ESTADOS][MAX_LEN];
                int tam_U = fecho_epsilon(move_res, tam_move, nfa_delta, num_trans_nfa, U_estados);

                int idx_U = -1;
                for(int j=0; j<num_dfa_states; j++){
                    if(conjuntos_iguais_str(dfa_states[j].estados_nfa, dfa_states[j].num_estados_nfa, U_estados, tam_U)){
                        idx_U = j;
                        break;
                    }
                }

                if(idx_U == -1){
                    EstadoDFA novo_U;
                    novo_U.nome = proximo_nome_dfa++;
                    novo_U.num_estados_nfa = tam_U;
                    // (FIX) Corrigido memcpy para copiar o tamanho exato, não o buffer máximo.
                    memcpy(novo_U.estados_nfa, U_estados, tam_U * sizeof(char) * MAX_LEN);
                    
                    idx_U = num_dfa_states;
                    dfa_states[num_dfa_states++] = novo_U;
                    fila_processamento[fim_fila++] = idx_U;
                }
                
                dfa_delta[num_dfa_trans].origem_nome = T.nome;
                strcpy(dfa_delta[num_dfa_trans].simbolo, simbolo_a);
                dfa_delta[num_dfa_trans].destino_nome = dfa_states[idx_U].nome;
                num_dfa_trans++;
            }
        }
        
        for(int i=0; i<num_dfa_states; i++){
            dfa_states[i].eh_final = 0;
            for(int j=0; j<dfa_states[i].num_estados_nfa; j++){
                if(pertence(dfa_states[i].estados_nfa[j], F, tamF)){
                    dfa_states[i].eh_final = 1;
                    break;
                }
            }
        }

        // SAÍDA DO AFD (impressão)
        printf("\n================ AFD RESULTANTE (D) ================\n");
        printf("Q_d = {");
        for(int i=0; i<num_dfa_states; i++){ printf("%c%s", dfa_states[i].nome, (i == num_dfa_states-1) ? "" : ", "); }
        printf("}\n\nDetalhamento dos Estados:\n");
        for(int i=0; i<num_dfa_states; i++){
            printf("  %c = <", dfa_states[i].nome);
            ordenar_conjunto_str(dfa_states[i].estados_nfa, dfa_states[i].num_estados_nfa);
            for(int j=0; j<dfa_states[i].num_estados_nfa; j++){
                printf("%s%s", dfa_states[i].estados_nfa[j], (j == dfa_states[i].num_estados_nfa-1) ? "" : ",");
            }
            printf(">\n");
        }
        printf("\nAlfabeto = {");
        for(int i=0; i<tamA; i++){ printf("'%s'%s", A[i], (i == tamA-1) ? "" : ", "); }
        printf("}\n");
        printf("\nq0_d = %c\n", dfa_states[0].nome);
        printf("\nF_d = {");
        int primeiro_final = 1;
        for(int i=0; i<num_dfa_states; i++){
            if(dfa_states[i].eh_final){
                if(!primeiro_final) printf(", ");
                printf("%c", dfa_states[i].nome);
                primeiro_final = 0;
            }
        }
        printf("}\n");
        printf("\ndelta_d:\n");
        for(int i=0; i<num_dfa_trans; i++){
            printf("  delta_d(%c, %s) = %c\n", dfa_delta[i].origem_nome, dfa_delta[i].simbolo, dfa_delta[i].destino_nome);
        }
        printf("===================================================\n");

        printf("\nDeseja converter outro AFN? (s/n): ");
        // (FIX) Adicionada verificação do retorno de scanf para robustez
        if (scanf(" %c", &opcao) != 1) {
            opcao = 'n'; // Assume 'não' em caso de erro de leitura
        }
        getchar(); // Limpa o buffer de entrada

    } while (opcao == 's' || opcao == 'S');

    printf("\nFim Feliz/Happy End/Finalizacion alegre\n");
    return 0;
}