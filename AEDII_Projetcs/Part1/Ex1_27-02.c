#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

struct s_no
{
    int info;
    struct s_no *prox;
};

// Procedimento iterativo para imprimir a lista
void imprime_lista(struct s_no *inicio)
{
    struct s_no *pont = inicio;
    while (pont != NULL)
    {
        printf("%i -> ", pont->info);
        pont = pont->prox;
    }
    printf("NULL\n"); // Indica o final da lista
}

int main()
{
    struct s_no *ptlista = NULL,
                *p1, *p2, *p3;

    // Aloca nós				
    p1 = malloc(sizeof(struct s_no));
    p2 = malloc(sizeof(struct s_no));
    p3 = malloc(sizeof(struct s_no));
    
    // Inicializa nós alocados (valores e encadeamento)
    p1->info = 1; 
    p1->prox = p2;
    p2->info = 2; 
    p2->prox = p3;
    p3->info = 3;
    p3->prox = NULL;
    ptlista = p1; // Inicializa ponteiro do início da lista 
    
    // Chama o procedimento para imprimir a lista
    imprime_lista(ptlista);

    // Desaloca memória
    free(p1);
    free(p2);
    free(p3);
    
    return 0;
}