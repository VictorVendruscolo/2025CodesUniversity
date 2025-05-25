#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 30
#define MAXLEN 20
#define TRAVOU "-1"

// Funcao par leitura segura de string
void getsCustom(char *str, int t, int *tamW)
{
    fgets(str, t, stdin);
    *tamW = strlen(str);
    if (*tamW > 0 && str[*tamW - 1] == '\n')
    {
        str[*tamW - 1] = '\0';
        (*tamW)--;
    }
}

// Divide string por espaco em matriz
void split(char M[MAX][MAXLEN], char *str, int *tam)
{
    int i = 0;
    char *token = strtok(str, " \n");
    while (token != NULL && i < MAX)
    {
        strcpy(M[i++], token);
        token = strtok(NULL, " \n");
    }
    *tam = i;
}

// Retorna indice de um elemento
int buscaIndice(char *elemento, char M[MAX][MAXLEN], int tam)
{
    for (int i = 0; i < tam; i++)
    {
        if (strcmp(elemento, M[i]) == 0)
            return i;
    }
    return -1;
}

// Verifica se elemento pertence a conjunto
int pertence(char *el, char M[MAX][MAXLEN], int tam)
{
    return buscaIndice(el, M, tam) != -1;
}

int main()
{
    // Geracao do README antes de iniciar
    FILE *readme = fopen("README.txt", "w");
    if (readme != NULL)
    {
        fprintf(readme,
                "AUTÔMATO FINITO DETERMINiSTICO (AFD)\n\n"
                "Este programa implementa um AFD interativo em C.\n\n"
                "---------------------------\n"
                "COMPILACAO (Unix/Linux):\n"
                "---------------------------\n\n"
                "$ gcc -o afd programa.c\n\n"
                "EXECUcaO:\n"
                "$ ./afd\n\n"
                "---------------------------\n"
                "ENTRADAS DO USUÁRIO:\n"
                "---------------------------\n"
                "1. Estados (ex: 0 1 2)\n"
                "2. Alfabeto (ex: a b ou 0 1)\n"
                "3. Estado inicial (ex: 0)\n"
                "4. Estados finais (ex: 2)\n"
                "5. Transicões delta (ex: delta(0, a) = 1)\n"
                "6. Palavra a testar (simbolos sem espaço: abba)\n\n"
                "---------------------------\n"
                "OBSERVAcÕES:\n"
                "---------------------------\n"
                "- Os estados devem ser nomes simples (preferencialmente números).\n"
                "- Os simbolos devem ser separados por espaco.\n"
                "- O simbolo de transicao ineistente e \"-1\".\n"
                "- O programa rejeita automaticamente entradas inválidas.\n"
                "- Aceita ate 30 estados e 30 simbolos.\n"
                "- Programa criado por Victor Rech Vendruscolo para disciplina de Linguagens Formais.\n");
        fclose(readme);
        printf("Arquivo README.txt gerado com instrucoes.\n");
    }
    else
    {
        printf("Erro ao criar README.txt.\n");
    }

    char A[MAX][MAXLEN], Q[MAX][MAXLEN], F[MAX][MAXLEN], delta[MAX][MAX][MAXLEN];
    char str[300], W[300], qAtual[MAXLEN];
    int tamA, tamQ, tamF, tamW;
    char opcao;

    do
    {
        printf("\n& Construindo Automato &\n");
        printf("\n");
        // ESTADOS
        printf("Entre com os estados (ex: 0 1 2): ");
        getsCustom(str, sizeof(str), &tamQ);
        split(Q, str, &tamQ);

        // ALFABETO
        printf("Entre com o alfabeto (ex: 0 1): ");
        getsCustom(str, sizeof(str), &tamA);
        split(A, str, &tamA);

        // ESTADO INICIAL
        printf("Estado inicial: ");
        scanf("%s", qAtual);
        getchar(); // consumir '\n'

        if (!pertence(qAtual, Q, tamQ))
        {
            printf("Erro: estado inicial \"%s\" nao esta entre os estados definidos.\n", qAtual);
            continue;
        }

        // ESTADOS FINAIS
        printf("Estados finais: ");
        getsCustom(str, sizeof(str), &tamF);
        split(F, str, &tamF);

        int ok = 1;
        for (int i = 0; i < tamF; i++)
        {
            if (!pertence(F[i], Q, tamQ))
            {
                printf("Erro: estado final \"%s\" nao esta entre os estados definidos.\n", F[i]);
                ok = 0;
            }
        }
        if (!ok)
            continue;

        // TRANSICÕES
        for (int i = 0; i < tamQ; i++)
        {
            for (int j = 0; j < tamA; j++)
            {
                while (1)
                {
                    printf("delta(%s, %s) = ", Q[i], A[j]);
                    scanf("%s", delta[i][j]);
                    if (pertence(delta[i][j], Q, tamQ) || strcmp(delta[i][j], TRAVOU) == 0)
                        break;
                    else
                        printf("Transicao invalida! \"%s\" nao eh um estado conhecido ou -1.\n", delta[i][j]);
                }
            }
        }
        getchar(); // limpar buffer

        // LACO DE TESTE DE PALAVRAS
        do
        {
            printf("\n& Aplicacao de Palavra &\n");
            printf("\n");
            printf("Digite a palavra (ex: abba): ");
            getsCustom(W, sizeof(W), &tamW);

            // Checar se todos simbolos pertencem ao alfabeto
            int invalido = 0;
            for (int k = 0; k < tamW; k++)
            {
                char simbolo_str[2] = {W[k], '\0'};
                if (!pertence(simbolo_str, A, tamA))
                {
                    printf("Erro: simbolo \"%c\" nao pertence ao alfabeto.\n", W[k]);
                    invalido = 1;
                }
            }
            if (invalido)
                continue;

            // Simulacao
            strcpy(qAtual, Q[0]);
            int travou = 0;

            printf("Sequencia: %s", qAtual);
            for (int k = 0; k < tamW; k++)
            {
                char simbolo_str[2] = {W[k], '\0'};
                int i = buscaIndice(qAtual, Q, tamQ);
                int j = buscaIndice(simbolo_str, A, tamA);
                if (i == -1 || j == -1 || strcmp(delta[i][j], TRAVOU) == 0)
                {
                    travou = 1;
                    break;
                }
                strcpy(qAtual, delta[i][j]);
                printf(" -> %s", qAtual);
            }

            if (!travou && pertence(qAtual, F, tamF))
                printf("\nPalavra reconhecida!\n");
            else
                printf("\nPalavra NAO reconhecida!\n");

            printf("Deseja testar outra palavra? (s/n): ");
            scanf(" %c", &opcao);
            getchar();
        } while (opcao == 's' || opcao == 'S');

        printf("Deseja criar outro automato? (s/n): ");
        scanf(" %c", &opcao);
        getchar();

    } while (opcao == 's' || opcao == 'S');

    printf("\nFim Feliz/Happy End/Finalizacion alegre\n");
    return 0;
}
