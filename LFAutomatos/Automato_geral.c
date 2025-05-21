#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 10      // máximo estados/símbolos
#define MAXLEN 10   // máximo tamanho de cada estado/símbolo
#define TRAVOU "-1" // símbolo de estado travado (não existe transição)

// Lê linha com fgets, remove newline e retorna tamanho
void getsCustom(char *str, int t, int *tamW)
{
    fgets(str, t, stdin);
    *tamW = strlen(str);
    if (str[*tamW - 1] == '\n')
    {
        str[*tamW - 1] = '\0';
        (*tamW)--;
    }
}

// Divide uma string por espaço e armazena cada token em uma matriz de strings
void split(char M[MAX][MAXLEN], char *str, int *tam)
{
    int i = 0;
    char *token = strtok(str, " \n");
    while (token != NULL && i < MAX)
    {
        strncpy(M[i], token, MAXLEN - 1);
        M[i][MAXLEN - 1] = '\0'; // garante terminação
        i++;
        token = strtok(NULL, " \n");
    }
    *tam = i;
}

// Retorna o índice de um elemento em uma matriz de strings
int buscaIndice(char *elemento, char M[MAX][MAXLEN], int tam)
{
    for (int i = 0; i < tam; i++)
    {
        if (strcmp(elemento, M[i]) == 0)
            return i;
    }
    return -1;
}

// Verifica se uma string pertence a um conjunto de strings
int pertence(char *el, char M[MAX][MAXLEN], int tam)
{
    return buscaIndice(el, M, tam) != -1;
}

int main()
{
    char A[MAX][MAXLEN], Q[MAX][MAXLEN], F[MAX][MAXLEN], delta[MAX][MAX][MAXLEN];
    char str[100], W[100], qAtual[MAXLEN], simbolo[MAXLEN];
    int tamA, tamQ, tamF, tamW;
    char opcao;

    do
    {
        printf("== CRIACAO DO AUTOMATO ==\n");

        printf("Entre com os estados (ex: 0 1 2): ");
        getsCustom(str, sizeof(str), &tamQ);
        split(Q, str, &tamQ);

        printf("Entre com o alfabeto (ex: 0 1): ");
        getsCustom(str, sizeof(str), &tamA);
        split(A, str, &tamA);

        printf("Estado inicial: ");
        getsCustom(qAtual, sizeof(qAtual), &tamW); // lê estado inicial como string

        printf("Estados finais: ");
        getsCustom(str, sizeof(str), &tamF);
        split(F, str, &tamF);

        // Leitura da matriz delta
        for (int i = 0; i < tamQ; i++)
        {
            for (int j = 0; j < tamA; j++)
            {
                printf("delta(%s, %s) = ", Q[i], A[j]);
                getsCustom(delta[i][j], MAXLEN, &tamW);
                // Permite digitar TRAVOU para estado travado
            }
        }

        do
        {
            printf("\n== TESTE DE PALAVRA ==\n");
            printf("Digite a palavra (simbolos separados por espaco): ");
            getsCustom(W, sizeof(W), &tamW);

            strcpy(qAtual, Q[0]); // começa no estado inicial
            int travou = 0;

            printf("Sequencia: %s", qAtual);
            char *token = strtok(W, " ");
            while (token != NULL)
            {
                strncpy(simbolo, token, MAXLEN - 1);
                simbolo[MAXLEN - 1] = '\0';

                int i = buscaIndice(qAtual, Q, tamQ);
                int j = buscaIndice(simbolo, A, tamA);
                if (i == -1 || j == -1)
                {
                    travou = 1;
                    break;
                }
                if (strcmp(delta[i][j], TRAVOU) == 0)
                {
                    travou = 1;
                    break;
                }
                strcpy(qAtual, delta[i][j]);
                printf(" -> %s", qAtual);
                token = strtok(NULL, " ");
            }

            if (!travou && pertence(qAtual, F, tamF))
                printf("\nPalavra reconhecida!\n");
            else
                printf("\nPalavra NAO reconhecida!\n");

            printf("Deseja testar outra palavra? (s/n): ");
            getsCustom(str, sizeof(str), &tamW);
            opcao = str[0];
        } while (opcao == 's' || opcao == 'S');

        printf("Deseja criar outro automato? (s/n): ");
        getsCustom(str, sizeof(str), &tamW);
        opcao = str[0];

    } while (opcao == 's' || opcao == 'S');

    printf("Encerrando o programa.\n");

    printf("Criando arquivo README.txt com instrucoes...\n");

    FILE *readme = fopen("README.txt", "w");
    if (readme != NULL)
    {
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

                "6. Palavra a ser testada:      Ex: a b b\n\n"

                "Após o teste da palavra, o usuário pode:\n"

                "- Testar nova palavra no mesmo autômato\n"

                "- Criar novo autômato\n"

                "- Encerrar o programa\n\n"

                "---------------------------\n"

                "OBSERVAÇÕES:\n"

                "---------------------------\n\n"

                "- Todos os estados devem ser números (ex: 0, 1, 2).\n"

                "- Os símbolos do alfabeto podem ser strings (ex: a, b, 10).\n"

                "- A entrada é feita por espaço. Não use vírgulas.\n"

                "- O programa trata apenas autômatos determinísticos (AFD).\n"

                "- Use \"" TRAVOU "\" para indicar transição inexistente.\n\n"

                "---------------------------\n"

                "DESENVOLVIDO POR: VICTOR RECH VENDRUSCOLO\n"

                "PARA: OSVALDO - LINGUAGEM FORMAL E AUTOMATOS\n");
        fclose(readme);
    }
    else
    {
        printf("Erro ao criar o arquivo README.txt.\n");
    }

    return 0;
}
