
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define MAX_DEGREE 10
#define MAX_ITERATIONS 1000

// Function to evaluate polynomial at a given x
double evaluatePolynomial(double coefficients[], int degree, double x) {
    double result = 0.0;
    for (int i = 0; i <= degree; i++) {
        result += coefficients[i] * pow(x, degree - i);
    }
    return result;
}

// Trabalho 3 - Root Isolation
void rootIsolation(double coefficients[], int degree, double a, double b) {
    printf("\n=== TRABALHO 3 - ISOLAMENTO DE RAIZES ===\n\n");

    clock_t start = clock();

    // Create table with x values and f(x) values
    printf("Tabela de valores:\n");
    printf("%-15s %-15s\n", "x", "f(x)");
    printf("%-15s %-15s\n", "---------------", "---------------");

    int rootCount = 0;
    double intervals[100][2];  // To store intervals containing roots

    // Check each interval of amplitude 1
    for (double x = a; x < b; x += 1.0) {
        double fx = evaluatePolynomial(coefficients, degree, x);
        double fx_next = evaluatePolynomial(coefficients, degree, x + 1.0);

        printf("%-15.7f %-15.7f\n", x, fx);

        // Check for sign change (Bolzano's theorem)
        if (fx * fx_next < 0) {
            intervals[rootCount][0] = x;
            intervals[rootCount][1] = x + 1.0;
            rootCount++;
        }
    }

    // Print last point
    double fx_last = evaluatePolynomial(coefficients, degree, b);
    printf("%-15.7f %-15.7f\n", b, fx_last);

    clock_t end = clock();
    double executionTime = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("\nQuantidade de raizes: %d\n", rootCount);

    if (rootCount == 0) {
        printf("\nNao existe raiz pertencente aos Reais.\n");
    } else {
        printf("\nIntervalos contendo raizes:\n");
        for (int i = 0; i < rootCount; i++) {
            printf("[%.7f, %.7f]\n", intervals[i][0], intervals[i][1]);
        }
    }

    printf("\nTempo de execucao: %.6f segundos\n", executionTime);
}

// Trabalho 4 - Bisection Method (CORRIGIDO)
void bisectionMethod(double coefficients[], int degree, double a, double b, double error) {
    printf("\n=== TRABALHO 4 - METODO DA BISSECCAO ===\n\n");

    clock_t start = clock();

    double fa = evaluatePolynomial(coefficients, degree, a);
    double fb = evaluatePolynomial(coefficients, degree, b);

    // Check Bolzano's theorem
    if (fa * fb >= 0) {
        printf("Erro: f(a) * f(b) >= 0. Nao ha garantia de raiz no intervalo [%.7f, %.7f]\n", a, b);
        return;
    }

    // CORRIGIDO: Nova estrutura da tabela
    printf("Tabela de iteracoes:\n");
    printf("%-5s %-15s %-15s %-15s %-15s %-15s\n", 
           "n", "a", "b", "xn", "f(xn)", "|xn-x(n-1)|");
    printf("%-5s %-15s %-15s %-15s %-15s %-15s\n",
           "-----", "---------------", "---------------", "---------------", 
           "---------------", "---------------");

    int n = 0;  // CORRIGIDO: iteração começando em 0
    double xn, fxn;
    double xn_anterior = 0.0;  // CORRIGIDO: para calcular |xn - x(n-1)|
    double erro_absoluto;

    do {
        xn = (a + b) / 2.0;  // CORRIGIDO: ponto médio chamado de xn
        fxn = evaluatePolynomial(coefficients, degree, xn);  // CORRIGIDO: f(xn)

        // CORRIGIDO: Calcular |xn - x(n-1)|
        if (n == 0) {
            erro_absoluto = 0.0;  // Na primeira iteração não há x anterior
            printf("%-5d %-15.7f %-15.7f %-15.7f %-15.7f %-15s\n",
                   n, a, b, xn, fxn, "-");
        } else {
            erro_absoluto = fabs(xn - xn_anterior);  // CORRIGIDO: |xn - x(n-1)|
            printf("%-5d %-15.7f %-15.7f %-15.7f %-15.7f %-15.7f\n",
                   n, a, b, xn, fxn, erro_absoluto);
        }

        // CORRIGIDO: Critério de parada usando |xn - x(n-1)|
        if (n > 0 && (erro_absoluto <= error || fabs(fxn) <= error)) {
            break;
        }

        // Guardar xn atual para próxima iteração
        xn_anterior = xn;

        // Choose the interval where the root is located
        if (fa * fxn < 0) {
            b = xn;
        } else {
            a = xn;
        }

        // Recalcular fa para próxima iteração
        fa = evaluatePolynomial(coefficients, degree, a);

        n++;  // CORRIGIDO: incrementar n

    } while (n == 1 || (erro_absoluto > error && fabs(fxn) > error && n < MAX_ITERATIONS));

    clock_t end = clock();
    double executionTime = ((double)(end - start)) / CLOCKS_PER_SEC;

    // CORRIGIDO: Saída simplificada sem estimativas
    printf("\nRaiz: %.7f\n", xn);
    printf("Tempo de execucao: %.6f segundos\n", executionTime);
}

void printMenu() {
    printf("\n=================================================\n");
    printf("    CALCULADORA DE ZEROS DE FUNCOES POLINOMIAIS\n");
    printf("=================================================\n");
    printf("1. Trabalho 3 - Isolamento de Raizes\n");
    printf("2. Trabalho 4 - Metodo da Bisseccao\n");
    printf("3. Sair\n");
    printf("=================================================\n");
    printf("Escolha uma opcao: ");
}

void readPolynomial(double coefficients[], int *degree) {
    printf("\nDigite o grau do polinomio (maximo %d): ", MAX_DEGREE);
    scanf("%d", degree);

    if (*degree < 0 || *degree > MAX_DEGREE) {
        printf("Erro: Grau invalido!\n");
        return;
    }

    printf("\nDigite os coeficientes do polinomio (em ordem decrescente de potencia):\n");
    printf("Polinomio: ");

    for (int i = 0; i <= *degree; i++) {
        printf("c%d*x^%d", i, *degree - i);
        if (i < *degree) printf(" + ");
    }
    printf(" = 0\n");

    for (int i = 0; i <= *degree; i++) {
        printf("Coeficiente c%d (x^%d): ", i, *degree - i);
        scanf("%lf", &coefficients[i]);
    }

    printf("\nPolinomio inserido: ");
    for (int i = 0; i <= *degree; i++) {
        if (i == 0) {
            printf("%.2fx^%d", coefficients[i], *degree - i);
        } else {
            if (coefficients[i] >= 0) {
                printf(" + %.2fx^%d", coefficients[i], *degree - i);
            } else {
                printf(" %.2fx^%d", coefficients[i], *degree - i);
            }
        }
    }
    printf("\n");
}

int main() {
    double coefficients[MAX_DEGREE + 1];
    int degree;
    double a, b, error;
    int choice;

    printf("=================================================\n");
    printf("    ZEROS DE FUNCOES - METODOS NUMERICOS\n");
    printf("    Implementacao dos Trabalhos 3 e 4\n");
    printf("=================================================\n");

    while (1) {
        printMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                // Trabalho 3 - Isolamento de Raizes
                readPolynomial(coefficients, &degree);

                printf("\nDigite o intervalo inicial [a, b]:\n");
                printf("a: ");
                scanf("%lf", &a);
                printf("b: ");
                scanf("%lf", &b);

                if (a >= b) {
                    printf("Erro: O intervalo deve ter a < b!\n");
                    break;
                }

                rootIsolation(coefficients, degree, a, b);
                break;

            case 2:
                // Trabalho 4 - Metodo da Bisseccao
                readPolynomial(coefficients, &degree);

                printf("\nDigite o intervalo inicial [a, b]:\n");
                printf("a: ");
                scanf("%lf", &a);
                printf("b: ");
                scanf("%lf", &b);

                if (a >= b) {
                    printf("Erro: O intervalo deve ter a < b!\n");
                    break;
                }

                printf("Digite o erro tolerado: ");
                scanf("%lf", &error);

                if (error <= 0) {
                    printf("Erro: A tolerancia deve ser positiva!\n");
                    break;
                }

                bisectionMethod(coefficients, degree, a, b, error);
                break;

            case 3:
                printf("\nEncerrando o programa...\n");
                printf("Obrigado por usar o calculadora de zeros de funcoes!\n");
                exit(0);

            default:
                printf("\nOpcao invalida! Tente novamente.\n");
                break;
        }

        printf("\nPressione Enter para continuar...");
        getchar(); // Clear the input buffer
        getchar(); // Wait for Enter
    }

    return 0;
}
