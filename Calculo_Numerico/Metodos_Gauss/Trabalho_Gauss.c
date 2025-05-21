#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define MAX 10

// Imprime uma matriz quadrada com 2 casas decimais
void print_matriz(double M[MAX][MAX], int ordem)
{
    for (int i = 0; i < ordem; i++)
    {
        for (int j = 0; j < ordem; j++)
        {
            printf("%.2lf\t", M[i][j]);
        }
        printf("\n");
    }
}

// Imprime um vetor com 9 casas decimais
void print_vetor(double vetor[MAX], int n)
{
    for (int i = 0; i < n; i++)
        printf("x%d = %.9lf\t", i + 1, vetor[i]);
    printf("\n");
}

// Imprime vetor com erro relativo a cada passo
void print_vetor_com_erro(double atual[MAX], double anterior[MAX], int n)
{
    for (int i = 0; i < n; i++)
    {
        double erro = fabs(atual[i] - anterior[i]) / (fabs(atual[i]) + 1e-10);
        printf("x%d = %.9lf\t(erro = %.9lf)\n", i + 1, atual[i], erro);
    }
    printf("\n");
}

// Imprime matriz aumentada [A | I]
void print_matriz_aumentada(double A[MAX][MAX], double I[MAX][MAX], int ordem)
{
    for (int i = 0; i < ordem; i++)
    {
        for (int j = 0; j < ordem; j++)
            printf("%.2lf\t", A[i][j]);
        printf("| ");
        for (int j = 0; j < ordem; j++)
            printf("%.2lf\t", I[i][j]);
        printf("\n");
    }
}

// Entrada de matriz interativa com exibi��o passo a passo
void ler_matriz(double A[MAX][MAX], int ordem)
{
    int total = ordem * ordem;
    int count = 0;

    printf("\nDigite os elementos da matriz %dx%d:\n", ordem, ordem);

    for (int i = 0; i < ordem; i++)
    {
        printf("\n Preenchendo linha %d:\n", i + 1);
        for (int j = 0; j < ordem; j++)
        {
            count++;
            printf("Elemento [%d][%d] (%d de %d): ", i + 1, j + 1, count, total);
            if (scanf("%lf", &A[i][j]) != 1)
            {
                printf("Entrada invalida.\n");
                exit(1);
            }
            printf("\nMatriz parcial:\n");
            print_matriz(A, ordem);
        }
    }
}

// Verifica se matriz � estritamente diagonal dominante
int verificar_dominancia_diagonal(double A[MAX][MAX], int n)
{
    for (int i = 0; i < n; i++)
    {
        double soma = 0.0;
        for (int j = 0; j < n; j++)
        {
            if (j != i)
                soma += fabs(A[i][j]);
        }
        if (fabs(A[i][i]) <= soma)
            return 0;
    }
    return 1;
}

// Verifica se todos os elementos da diagonal s�o diferentes de zero
int verificar_diagonal_nao_nula(double A[MAX][MAX], int n)
{
    for (int i = 0; i < n; i++)
    {
        if (fabs(A[i][i]) < 1e-10)
            return 0;
    }
    return 1;
}

// M�todo de Jordan com pivota��o parcial
void inverter_matriz_jordan(int ordem, double A[MAX][MAX])
{
    double I[MAX][MAX] = {0};
    double temp;
    int i, j, k, max_row, trocas = 0;
    double det = 1.0;

    for (i = 0; i < ordem; i++)
        I[i][i] = 1.0;

    printf("\nMatriz aumentada inicial [A | I]:\n");
    print_matriz_aumentada(A, I, ordem);

    for (k = 0; k < ordem; k++)
    {
        max_row = k;
        for (i = k + 1; i < ordem; i++)
        {
            if (fabs(A[i][k]) > fabs(A[max_row][k]))
                max_row = i;
        }
        if (fabs(A[max_row][k]) < 1e-10)
        {
            printf("\nDeterminante eh zero\n");
            return;
        }
        if (max_row != k)
        {
            trocas++;
            for (j = 0; j < ordem; j++)
            {
                temp = A[k][j];
                A[k][j] = A[max_row][j];
                A[max_row][j] = temp;
                temp = I[k][j];
                I[k][j] = I[max_row][j];
                I[max_row][j] = temp;
            }
            printf("\n[Etapa %d] Pivotacao: trocando linha %d com linha %d\n", k + 1, k + 1, max_row + 1);
        }

        temp = A[k][k];
        det *= temp;
        for (j = 0; j < ordem; j++)
        {
            A[k][j] /= temp;
            I[k][j] /= temp;
        }
        printf("\n[Etapa %d] Normalizando linha %d (pivo = %.2lf):\n", k + 1, k + 1, temp);
        print_matriz_aumentada(A, I, ordem);

        for (i = 0; i < ordem; i++)
        {
            if (i != k)
            {
                temp = A[i][k];
                for (j = 0; j < ordem; j++)
                {
                    A[i][j] -= temp * A[k][j];
                    I[i][j] -= temp * I[k][j];
                }
            }
        }
        printf("\n[Etapa %d] Zerando coluna %d:\n", k + 1, k + 1);
        print_matriz_aumentada(A, I, ordem);
    }

    if (trocas % 2 != 0)
        det = -det;

    printf("\nDeterminante = %.2lf\n", det);
    if (fabs(det) < 1e-10)
    {
        printf("Matriz singular! Nao possui inversa.\n");
        return;
    }

    printf("\nMatriz inversa:\n");
    print_matriz(I, ordem);
}

// M�todo de Jacobi iterativo com verifica��o de converg�ncia
void resolver_jacobi(int n, double A[MAX][MAX], double b[MAX], double X0[MAX], double epsilon)
{
    double X[MAX], X_anterior[MAX];
    int iter = 0;
    int convergiu = 0;

    for (int i = 0; i < n; i++)
        X[i] = X0[i];

    clock_t inicio = clock();

    printf("\nIteracao %d:\n", iter);
    print_vetor(X, n);

    do
    {
        iter++;
        for (int i = 0; i < n; i++)
            X_anterior[i] = X[i];

        for (int i = 0; i < n; i++)
        {
            double soma = 0.0;
            for (int j = 0; j < n; j++)
            {
                if (j != i)
                    soma += A[i][j] * X_anterior[j];
            }
            X[i] = (b[i] - soma) / A[i][i];
        }

        printf("Iteracao %d:\n", iter);
        print_vetor_com_erro(X, X_anterior, n);

        convergiu = 1;
        for (int i = 0; i < n; i++)
        {
            if (fabs(X[i] - X_anterior[i]) / (fabs(X[i]) + 1e-10) >= epsilon)
            {
                convergiu = 0;
                break;
            }
        }

    } while (!convergiu);

    clock_t fim = clock();
    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;

    printf("\nSolucao final apos %d iteracoes:\n", iter);
    print_vetor(X, n);
    printf("Tempo de execucao: %.6lf segundos\n", tempo);
}

// Entrada de dados para m�todo de Jacobi
void entrada_jacobi()
{
    int n;
    double A[MAX][MAX], b[MAX], X0[MAX], epsilon;

    printf("Digite o numero de incognitas (1 a %d): ", MAX);
    scanf("%d", &n);
    if (n < 1 || n > MAX)
    {
        printf("Numero invalido.\n");
        return;
    }

    printf("Digite a matriz dos coeficientes (linha por linha):\n");
    for (int i = 0; i < n; i++)
    {
        printf("Linha %d:\n", i + 1);
        for (int j = 0; j < n; j++)
        {
            printf("A[%d][%d] = ", i + 1, j + 1);
            scanf("%lf", &A[i][j]);
        }
    }

    if (!verificar_diagonal_nao_nula(A, n))
    {
        printf("Erro: elementos diagonais nulos.\n");
        return;
    }

    if (!verificar_dominancia_diagonal(A, n))
    {
        printf("Aviso: a matriz nao eh diagonalmente dominante. O metodo de Jacobi pode nao convergir.\n");
    }

    printf("Digite o vetor de termos independentes b:\n");
    for (int i = 0; i < n; i++)
    {
        printf("b[%d] = ", i + 1);
        scanf("%lf", &b[i]);
    }

    printf("Digite a aproximacao inicial X0:\n");
    for (int i = 0; i < n; i++)
    {
        printf("x0[%d] = ", i + 1);
        scanf("%lf", &X0[i]);
    }

    printf("Digite a precisao (ex: 0.000000001): ");
    scanf("%lf", &epsilon);

    resolver_jacobi(n, A, b, X0, epsilon);
}

int main()
{
    int opcao, ordem;
    double matriz[MAX][MAX];
    int continuar = 1;

    while (continuar)
    {
        printf("\nTrabalho 1 e 2 - Calculo Numerico 2025\n");
        printf("\n");
        printf("1 - Inversao de matriz (Jordan)\n");
        printf("2 - Resolucao de sistema (Jacobi)\n");
        printf("0 - Sair\n");
        printf("\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            printf("Digite a ordem da matriz (1 a %d): ", MAX);
            scanf("%d", &ordem);
            if (ordem < 1 || ordem > MAX)
            {
                printf("Ordem invalida!\n");
                break;
            }
            ler_matriz(matriz, ordem);
            clock_t inicio = clock();
            inverter_matriz_jordan(ordem, matriz);
            clock_t fim = clock();
            printf("\nTempo de execucao: %.4lf segundos\n", (double)(fim - inicio) / CLOCKS_PER_SEC);
            break;

        case 2:
            entrada_jacobi();
            break;

        case 0:
            continuar = 0;
            break;

        default:
            printf("Opcao invalida\n");
        }

        if (continuar)
        {
            printf("\nPressione Enter para continuar...");
            while (getchar() != '\n')
                ;
            getchar();
        }
    }

    return 0;
}
