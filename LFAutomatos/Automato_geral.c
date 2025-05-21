#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 10
#define TRAVOU "x"

void gets_custom(char *str, int t, int *tamW){
    fgets(str, t, stdin);
    *tamW = strlen(str);
    if (*tamW > 0 && str[*tamW - 1] == '\n') {
        str[*tamW - 1] = '\0';
        (*tamW)--;
    }
}

// Separa strings por espaço
void split(char Q[MAX][MAX], char *str, int *tam){
    int i = 0;
    char *tok = strtok(str, " ");
    while (tok != NULL && i < MAX) {
        strcpy(Q[i++], tok);
        tok = strtok(NULL, " ");
    }
    *tam = i;
}

// Retorna índice se s pertence ao vetor V
int pertence(char *s, char V[MAX][MAX], int tam){
    for (int i = 0; i < tam; i++)
        if (strcmp(s, V[i]) == 0)
            return i;
    return -1;
}

char* delta(char *q, char c, char Q[MAX][MAX], int tamQ, char A[MAX], int tamA, char mDelta[MAX][MAX]){
    int i = pertence(q, Q, tamQ);
    int j = -1;
    for (int k = 0; k < tamA; k++)
        if (A[k] == c)
            j = k;
    if (i == -1 || j == -1)
        return TRAVOU;
    return mDelta[i][j] == '\0' ? TRAVOU : &mDelta[i][j];
}

int main(){
    char W[50], Q[MAX][MAX], F[MAX][MAX], str[100], *estadoAtual;
    char A[MAX], mDelta[MAX][MAX];
    int tamQ, tamA, tamF, tamW, opcao, p, Falha;
    char qo[MAX];
    
    do {
        printf("Entre com o conjunto de estados (ex: 0 1 2): ");
        gets_custom(str, 100, &tamQ);
        split(Q, str, &tamQ);

        printf("Entre com os simbolos do alfabeto (ex: a b): ");
        gets_custom(str, 100, &tamA);
        for(int i = 0; i < tamA; i++) A[i] = str[i * 2];  // assume 1 letra + 1 espaço

        printf("Entre com o estado inicial: ");
        scanf("%s", qo); getchar();

        printf("Entre com os estados finais (ex: 1 2): ");
        gets_custom(str, 100, &tamF);
        split(F, str, &tamF);

        // Matriz de transição
        printf("\n--- Defina as transicoes ---\n");
        for(int i = 0; i < tamQ; i++){
            for(int j = 0; j < tamA; j++){
                printf("delta(%s, %c) = ", Q[i], A[j]);
                scanf(" %c", &mDelta[i][j]);
                getchar();
            }
        }

        do {
            printf("\nEntre com a palavra a ser verificada: ");
            gets_custom(W, 50, &tamW);

            estadoAtual = qo;
            p = 0;
            Falha = 0;

            printf("Sequencia de estados: %s", estadoAtual);
            while(W[p] != '\0'){
                estadoAtual = delta(estadoAtual, W[p], Q, tamQ, A, tamA, mDelta);
                if(strcmp(estadoAtual, TRAVOU) == 0){
                    Falha = 1;
                    break;
                }
                printf(" -> %s", estadoAtual);
                p++;
            }

            if(!Falha && pertence(estadoAtual, F, tamF) != -1)
                printf("\nPalavra reconhecida!\n");
            else
                printf("\nPalavra nao reconhecida.\n");

            printf("\n[1] Testar nova palavra\n[2] Criar outro automato\n[3] Encerrar\nOpcao: ");
            scanf("%d", &opcao); getchar();
        } while(opcao == 1);

    } while(opcao == 2);

    printf("\nEncerrando o programa.\n");

        //README.TXT

        FILE *readme = fopen("README.txt", "w");
    if (readme != NULL) {
        fprintf(readme,
        "AUTÔMATO FINITO DETERMINÍSTICO (AFD)\n\n"


        "Este programa implementa um AFD interativo em C.\n"

        "Permite criar autômatos com estados numéricos, alfabeto com símbolos simples,\n"

        "e testar múltiplas palavras antes de encerrar.\n\n"


        "---------------------------\n"

        "COMPILAÇÃO (em Unix/Linux):\n"

        "---------------------------\n\n"


        "$ gcc -o afd programa.c\n\n"


        "Onde:\n"

        "- \"programa.c\" é o nome do arquivo com o código-fonte.\n"

        "- \"afd\" será o executável gerado.\n\n"

        "---------------------------\n"

        "EXECUÇÃO:\n"

        "---------------------------\n\n"


        "$ ./afd\n\n"


        "O programa solicitará as seguintes entradas, todas separadas por espaço:\n\n"


        "1. Conjunto de estados:        Ex: 0 1 2\n"

        "2. Símbolos do alfabeto:       Ex: a b\n"

        "3. Estado inicial:             Ex: 0\n"

        "4. Estados finais:             Ex: 2\n"

        "5. Transições (delta):         Para cada (estado, símbolo), insira o estado destino\n"

        "6. Palavra a ser testada:      Ex: abb\n\n"

        "Após o teste da palavra, o usuário pode:\n"

        "- Testar nova palavra no mesmo autômato\n"

        "- Criar novo autômato\n"

        "- Encerrar o programa\n\n"


        "---------------------------\n"

        "OBSERVAÇÕES:\n"

        "---------------------------\n\n"


        "- Todos os estados devem ser números (ex: 0, 1, 2).\n"

        "- Os símbolos do alfabeto devem ser caracteres únicos (ex: a, b, c).\n"

        "- A entrada é feita por espaço. Não use vírgulas.\n"

        "- O programa trata apenas autômatos determinísticos (AFD).\n"

        "- O símbolo de travamento (quando uma transição não existe) é tratado internamente.\n\n"


        "---------------------------\n"

        "DESENVOLVIDO POR: VICTOR RECH VENDRUSCOLO\n"

        "PARA: OSVALDO - LINGUAGEM FORMAL E AUTOMATOS\n"
        );
        fclose(readme);
    } else {
        printf("Erro ao criar o arquivo README.txt.\n");
    }


return 0;
}
