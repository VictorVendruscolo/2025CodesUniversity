#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define MAX_SIZE 10
#define MAX_ITER 1000

// Metodo de Jordan para matriz inversa
void metodoJordan()
{
    int n, i, j, k;
    double m[MAX_SIZE][MAX_SIZE], id[MAX_SIZE][MAX_SIZE];
    double temp, mult;
    clock_t inicio, fim;
    double tempo;

    printf("\nMetodo Jordan para Inversao\n\n");

    // Entrada da ordem da matriz
    printf("Ordem da matriz (max %d): ", MAX_SIZE);
    scanf("%d", &n);
    if (n <= 0 || n > MAX_SIZE)
    {
        printf("Ordem invalida!\n");
        return;
    }

    // Leitura da matriz
    printf("Digite a matriz:\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
        {
            printf("m[%d][%d]: ", i + 1, j + 1);
            scanf("%lf", &m[i][j]);
        }

    // Inicializa matriz identidade
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            id[i][j] = (i == j) ? 1.0 : 0.0;

    inicio = clock();

    // Passo 1: Eliminação fora da diagonal (Zerar)
    for (i = 0; i < n; i++)
    {
        // Pivoteamento parcial
        int pivo_linha = i;
        for (k = i + 1; k < n; k++)
            if (fabs(m[k][i]) > fabs(m[pivo_linha][i]))
                pivo_linha = k;

        // Troca de linhas se necessário
        if (pivo_linha != i)
        {
            printf("\nTroca: L%d <-> L%d\n", i + 1, pivo_linha + 1);
            for (j = 0; j < n; j++)
            {
                temp = m[i][j];
                m[i][j] = m[pivo_linha][j];
                m[pivo_linha][j] = temp;

                temp = id[i][j];
                id[i][j] = id[pivo_linha][j];
                id[pivo_linha][j] = temp;
            }
        }

        // Verifica se o pivô é zero
        if (fabs(m[i][i]) < 1e-10)
        {
            printf("Matriz singular. Nao possui inversa.\n");
            return;
        }

        // Zera todos os elementos da coluna i (menos o pivô)
        for (k = 0; k < n; k++)
        {
            if (k != i)
            {
                mult = m[k][i] / m[i][i];
                printf("\nL%d = L%d - (%.2f * L%d)\n", k + 1, k + 1, mult, i + 1);
                for (j = 0; j < n; j++)
                {
                    m[k][j] -= mult * m[i][j];
                    id[k][j] -= mult * id[i][j];
                }
            }
        }

        // Imprime após zerar a coluna i
        printf("\nMatriz m apos zerar coluna %d:\n", i + 1);
        for (k = 0; k < n; k++)
        {
            for (j = 0; j < n; j++)
                printf("%.2f\t", m[k][j]);
            printf("\n");
        }

        printf("\nMatriz id apos zerar coluna %d:\n", i + 1);
        for (k = 0; k < n; k++)
        {
            for (j = 0; j < n; j++)
                printf("%.2f\t", id[k][j]);
            printf("\n");
        }
    }

    // Passo 2: Normalização da diagonal
    printf("\nNormalizando as linhas...\n");
    for (i = 0; i < n; i++)
    {
        double pivo = m[i][i];
        printf("L%d = L%d / %.2f\n", i + 1, i + 1, pivo);
        for (j = 0; j < n; j++)
        {
            m[i][j] /= pivo;
            id[i][j] /= pivo;
        }
    }

    fim = clock();
    tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;

    // Resultado
    printf("\nResultado\n\n");
    printf("Matriz original transformada em identidade:\n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
            printf("%.2f\t", m[i][j]);
        printf("\n");
    }

    printf("\nMatriz inversa:\n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
            printf("%.2f\t", id[i][j]);
        printf("\n");
    }

    printf("\nTempo de execucao: %.6f segundos\n", tempo);
}

// Metodo de Jacobi para sistemas lineares
void metodoJacobi()
{
    int n, i, j, k, iter = 0;
    double A[MAX_SIZE][MAX_SIZE], b[MAX_SIZE];
    double x[MAX_SIZE], x_ant[MAX_SIZE];
    double max_erro, precisao;
    double soma, temp;
    clock_t inicio, fim;
    double tempo;

    printf("\nSolucao de Sistema com Jacobi\n");
    printf("\n");

    // Entrada
    printf("Qual o numero de incognitas? (max %d): ", MAX_SIZE);
    scanf("%d", &n);
    if (n <= 0 || n > MAX_SIZE)
    {
        printf("Numero invalido!\n");
        return;
    }

    printf("Digite os coeficientes da matriz:\n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            printf("A[%d][%d]: ", i + 1, j + 1);
            scanf("%lf", &A[i][j]);
        }
    }

    printf("Digite os termos independentes:\n");
    for (i = 0; i < n; i++)
    {
        printf("b[%d]: ", i + 1);
        scanf("%lf", &b[i]);
    }

    printf("Digite a precisao: ");
    scanf("%lf", &precisao);

    printf("Digite a solucao inicial:\n");
    for (i = 0; i < n; i++)
    {
        printf("x[%d]: ", i + 1);
        scanf("%lf", &x_ant[i]);
    }

    // Verifica se a matriz é diagonalmente dominante
    int dominante = 1;
    for (i = 0; i < n; i++)
    {
        soma = 0;
        for (j = 0; j < n; j++)
        {
            if (i != j)
                soma += fabs(A[i][j]);
        }
        if (fabs(A[i][i]) <= soma)
        {
            dominante = 0;

            // Tenta reorganizar linhas
            double max_elem = fabs(A[i][i]);
            int max_linha = i;
            for (k = i + 1; k < n; k++)
            {
                if (fabs(A[k][i]) > max_elem)
                {
                    max_elem = fabs(A[k][i]);
                    max_linha = k;
                }
            }

            if (max_linha != i)
            {
                printf("Reorganizando: Linha %d -> Linha %d\n", max_linha + 1, i + 1);
                for (j = 0; j < n; j++)
                {
                    temp = A[i][j];
                    A[i][j] = A[max_linha][j];
                    A[max_linha][j] = temp;
                }
                temp = b[i];
                b[i] = b[max_linha];
                b[max_linha] = temp;
            }
        }
    }

    // Verifica diagonal
    for (i = 0; i < n; i++)
    {
        if (fabs(A[i][i]) < 1e-10)
        {
            printf("Elemento da diagonal nulo\n");
            break;
        }
    }

    printf("\nMatriz %s diagonalmente dominante.\n",
           dominante ? "" : " NAO");

    inicio = clock();

    // Implementacao do metodo de Jacobi
    printf("\nIteracoes:\n");
    do
    {
        // Calcula nova aproximação
        for (i = 0; i < n; i++)
        {
            soma = 0;
            for (j = 0; j < n; j++)
            {
                if (j != i)
                    soma += A[i][j] * x_ant[j];
            }
            x[i] = (b[i] - soma) / A[i][i];
        }

        // Cálculo do erro
        double d = 0.0, max_x = 0.0;
        for (i = 0; i < n; i++)
        {
            double dif = fabs(x[i] - x_ant[i]);
            if (dif > d)
                d = dif;

            if (fabs(x[i]) > max_x)
                max_x = fabs(x[i]);

            // Atualiza x_ant para próxima iteração
            x_ant[i] = x[i];
        }

        // Erro relativo máximo
        if (max_x > 1e-10)
            max_erro = d / max_x;
        else
            max_erro = d;

        iter++;

        // Mostra iteração atual
        printf("\nIteracao %d:\n", iter);
        printf("\n");
        printf("Solucao: ");
        for (i = 0; i < n; i++)
            printf("%.9f ", x[i]);
        printf("\nErro relativo: %.9f\n", max_erro);

    } while (max_erro > precisao && iter < MAX_ITER);

    fim = clock();
    tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;

    // Resultado
    printf("\nFim itercoes\n");
    printf("\n");
    if (iter >= MAX_ITER)
    {
        printf("Aviso: Nao convergiu em %d iteracoes!\n", MAX_ITER);
    }
    else
    {
        printf("Convergiu em %d iteracoes!\n", iter);
    }

    printf("Solucao final:\n");
    for (i = 0; i < n; i++)
    {
        printf("x[%d] = %.9f\n", i + 1, x[i]);
    }

    // Cálculo do resíduo: |Ax - b|
    printf("\nResiduos:\n");
    for (i = 0; i < n; i++)
    {
        soma = 0;
        for (j = 0; j < n; j++)
        {
            soma += A[i][j] * x[j];
        }
        // Cálculo do resíduo: |Ax - b|
        printf("Eq %d: %.9f\n", i + 1, fabs(soma - b[i]));
    }

    printf("\nTempo de execucao: %.6f segundos\n", tempo);
}

int main()
{
    int opcao, continuar = 1;

    while (continuar)
    {
        printf("\nTrabalho 1 e 2  - 2025\n");
        printf("\n");
        printf("1 - Matriz inversa (Jordan)\n");
        printf("2 - Sistema linear (Jacobi)\n");
        printf("0 - Sair\n");
        printf("\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            metodoJordan();
            break;
        case 2:
            metodoJacobi();
            break;
        case 0:
            continuar = 0;
            break;
        default:
            printf("\n");
            printf("Opcao invalida!\n");
        }

        if (continuar)
        {
            printf("\nContinuar? (1-Sim / 0-Nao): ");
            scanf("%d", &continuar);
        }
    }

    return 0;
}