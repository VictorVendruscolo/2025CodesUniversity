// Trabalho de AED-II - Estruturas de Dados
// Listas, Pilhas e Filas
// Victor Rech Vendruscolo
// 2025/05/25

#include <stdlib.h>
#include <stdio.h>

// Estruturas de dados
typedef struct No
{
    int dado;
    struct No *ptprox;
} No;

typedef struct NoDuplo
{
    int dado;
    struct NoDuplo *ptprox;
    struct NoDuplo *ptant;
} NoDuplo;

// ==================== LISTA SIMPLESMENTE ENCADEADA ORDENADA ====================

// Função para imprimir lista simplesmente encadeada
void imprimirListaSimples(No *inicio)
{
    if (inicio == NULL)
    {
        printf("Lista vazia.\n");
        return;
    }

    printf("Lista: ");
    No *atual = inicio;
    while (atual != NULL)
    {
        printf("%d", atual->dado);
        if (atual->ptprox != NULL)
        {
            printf(" -> ");
        }
        atual = atual->ptprox;
    }
    printf(" -> NULL\n");
}

// Função para buscar elemento na lista simplesmente encadeada
int buscarListaSimples(No *inicio, int valor)
{
    No *atual = inicio;
    int posicao = 0;

    while (atual != NULL)
    {
        if (atual->dado == valor)
        {
            return posicao;
        }
        atual = atual->ptprox;
        posicao++;
    }
    return -1; // Nao encontrado
}

// Função para inserir ordenadamente na lista simplesmente encadeada
No *inserirListaSimples(No *inicio, int valor)
{
    No *novo = (No *)malloc(sizeof(No));
    if (novo == NULL)
    {
        printf("Erro na alocacao de memoria!\n");
        return inicio;
    }

    novo->dado = valor;
    novo->ptprox = NULL;

    // Lista vazia ou inserir no início
    if (inicio == NULL || valor <= inicio->dado)
    {
        novo->ptprox = inicio;
        return novo;
    }

    // Procurar posicao para inserir
    No *atual = inicio;
    while (atual->ptprox != NULL && atual->ptprox->dado < valor)
    {
        atual = atual->ptprox;
    }

    novo->ptprox = atual->ptprox;
    atual->ptprox = novo;

    return inicio;
}

// Função para remover elemento da lista simplesmente encadeada
No *removerListaSimples(No *inicio, int valor)
{
    if (inicio == NULL)
    {
        printf("Lista vazia. Nada para remover.\n");
        return NULL;
    }

    // Remover do início
    if (inicio->dado == valor)
    {
        No *temp = inicio;
        inicio = inicio->ptprox;
        free(temp);
        printf("Elemento %d removido com sucesso.\n", valor);
        return inicio;
    }

    // Procurar elemento
    No *atual = inicio;
    while (atual->ptprox != NULL && atual->ptprox->dado != valor)
    {
        atual = atual->ptprox;
    }

    if (atual->ptprox == NULL)
    {
        printf("Elemento %d nao encontrado.\n", valor);
        return inicio;
    }

    No *temp = atual->ptprox;
    atual->ptprox = temp->ptprox;
    free(temp);
    printf("Elemento %d removido com sucesso.\n", valor);

    return inicio;
}

// Função para desalocar lista simplesmente encadeada
void desalocarListaSimples(No *inicio)
{
    while (inicio != NULL)
    {
        No *temp = inicio;
        inicio = inicio->ptprox;
        free(temp);
    }
}

// ==================== LISTA CIRCULAR SIMPLESMENTE ENCADEADA ORDENADA ====================

// Função para imprimir lista circular
void imprimirListaCircular(No *inicio)
{
    if (inicio == NULL)
    {
        printf("Lista circular vazia.\n");
        return;
    }

    printf("Lista circular: ");
    No *atual = inicio;
    do
    {
        printf("%d", atual->dado);
        atual = atual->ptprox;
        if (atual != inicio)
        {
            printf(" -> ");
        }
    } while (atual != inicio);
    printf(" -> [volta ao inicio]\n");
}

int buscarListaCircular(No *inicio, int valor)
{
    if (inicio == NULL)
    {
        return -1; // Lista vazia
    }

    No *atual = inicio;
    int posicao = 0;

    do
    {
        if (atual->dado == valor)
        {
            return posicao;
        }
        atual = atual->ptprox;
        posicao++;
    } while (atual != inicio);

    return -1; // Não encontrado
}

// Função para inserir ordenadamente na lista circular
No *inserirListaCircular(No *inicio, int valor)
{
    No *novo = (No *)malloc(sizeof(No));
    if (novo == NULL)
    {
        printf("Erro na alocacao de memoria!\n");
        return inicio;
    }

    novo->dado = valor;

    // Lista vazia
    if (inicio == NULL)
    {
        novo->ptprox = novo; // Aponta para si mesmo
        return novo;
    }

    // Um só elemento ou inserir antes do primeiro
    if (inicio->ptprox == inicio || valor <= inicio->dado)
    {
        // Encontrar último No
        No *ultimo = inicio;
        while (ultimo->ptprox != inicio)
        {
            ultimo = ultimo->ptprox;
        }

        if (valor <= inicio->dado)
        {
            // Inserir no início
            novo->ptprox = inicio;
            ultimo->ptprox = novo;
            return novo; // Novo início
        }
    }

    // Procurar posicao para inserir
    No *atual = inicio;
    while (atual->ptprox != inicio && atual->ptprox->dado < valor)
    {
        atual = atual->ptprox;
    }

    novo->ptprox = atual->ptprox;
    atual->ptprox = novo;

    return inicio;
}

// Função para remover elemento da lista circular
No *removerListaCircular(No *inicio, int valor)
{
    if (inicio == NULL)
    {
        printf("Lista circular vazia. Nada para remover.\n");
        return NULL;
    }

    // Um só elemento
    if (inicio->ptprox == inicio && inicio->dado == valor)
    {
        free(inicio);
        printf("Elemento %d removido com sucesso.\n", valor);
        return NULL;
    }

    // Remover do início
    if (inicio->dado == valor)
    {
        // Encontrar último No
        No *ultimo = inicio;
        while (ultimo->ptprox != inicio)
        {
            ultimo = ultimo->ptprox;
        }

        No *temp = inicio;
        inicio = inicio->ptprox;
        ultimo->ptprox = inicio;
        free(temp);
        printf("Elemento %d removido com sucesso.\n", valor);
        return inicio;
    }

    // Procurar elemento
    No *atual = inicio;
    while (atual->ptprox != inicio && atual->ptprox->dado != valor)
    {
        atual = atual->ptprox;
    }

    if (atual->ptprox == inicio)
    {
        printf("Elemento %d nao encontrado.\n", valor);
        return inicio;
    }

    No *temp = atual->ptprox;
    atual->ptprox = temp->ptprox;
    free(temp);
    printf("Elemento %d removido com sucesso.\n", valor);

    return inicio;
}

// ==================== LISTA DUPLAMENTE ENCADEADA COM No CABEcA ====================

// Função para inicializar lista duplamente encadeada com No cabeca
NoDuplo *inicializarListaDupla()
{
    NoDuplo *cabeca = (NoDuplo *)malloc(sizeof(NoDuplo));
    if (cabeca == NULL)
    {
        printf("Erro na alocacao de memoria!\n");
        return NULL;
    }

    cabeca->dado = 0; // No cabeca nao armazena dado útil
    cabeca->ptprox = cabeca;
    cabeca->ptant = cabeca;

    return cabeca;
}

// Função para imprimir lista duplamente encadeada
void imprimirListaDupla(NoDuplo *cabeca)
{
    if (cabeca == NULL || cabeca->ptprox == cabeca)
    {
        printf("Lista duplamente encadeada vazia.\n");
        return;
    }

    printf("Lista duplamente encadeada: NULL <- ");
    NoDuplo *atual = cabeca->ptprox;
    while (atual != cabeca)
    {
        printf("%d", atual->dado);
        if (atual->ptprox != cabeca)
        {
            printf(" <-> ");
        }
        atual = atual->ptprox;
    }
    printf(" -> NULL\n");
}

// Função para inserir no final da lista duplamente encadeada
void inserirListaDupla(NoDuplo *cabeca, int valor)
{
    if (cabeca == NULL)
        return;

    NoDuplo *novo = (NoDuplo *)malloc(sizeof(NoDuplo));
    if (novo == NULL)
    {
        printf("Erro na alocacao de memoria!\n");
        return;
    }

    novo->dado = valor;

    // Inserir antes do No cabeca (no final da lista)
    novo->ptprox = cabeca;
    novo->ptant = cabeca->ptant;
    cabeca->ptant->ptprox = novo;
    cabeca->ptant = novo;
}

// Função para remover elemento da lista duplamente encadeada
void removerListaDupla(NoDuplo *cabeca, int valor)
{
    if (cabeca == NULL || cabeca->ptprox == cabeca)
    {
        printf("Lista duplamente encadeada vazia. Nada para remover.\n");
        return;
    }

    NoDuplo *atual = cabeca->ptprox;
    while (atual != cabeca && atual->dado != valor)
    {
        atual = atual->ptprox;
    }

    if (atual == cabeca)
    {
        printf("Elemento %d nao encontrado.\n", valor);
        return;
    }

    atual->ptant->ptprox = atual->ptprox;
    atual->ptprox->ptant = atual->ptant;
    free(atual);
    printf("Elemento %d removido com sucesso.\n", valor);
}

// ==================== FILA (FIFO) ====================

typedef struct
{
    No *inicio;
    No *fim;
} Fila;

// Função para inicializar fila
Fila *inicializarFila()
{
    Fila *fila = (Fila *)malloc(sizeof(Fila));
    if (fila == NULL)
    {
        printf("Erro na alocacao de memoria!\n");
        return NULL;
    }

    fila->inicio = NULL;
    fila->fim = NULL;
    return fila;
}

// Função para imprimir fila
void imprimirFila(Fila *fila)
{
    if (fila == NULL || fila->inicio == NULL)
    {
        printf("Fila vazia.\n");
        return;
    }

    printf("Fila (início -> fim): ");
    No *atual = fila->inicio;
    while (atual != NULL)
    {
        printf("%d", atual->dado);
        if (atual->ptprox != NULL)
        {
            printf(" -> ");
        }
        atual = atual->ptprox;
    }
    printf("\n");
}

// Função para inserir na fila (enqueue)
void enqueue(Fila *fila, int valor)
{
    if (fila == NULL)
        return;

    No *novo = (No *)malloc(sizeof(No));
    if (novo == NULL)
    {
        printf("Erro na alocacao de memoria!\n");
        return;
    }

    novo->dado = valor;
    novo->ptprox = NULL;

    if (fila->fim == NULL)
    {
        fila->inicio = fila->fim = novo;
    }
    else
    {
        fila->fim->ptprox = novo;
        fila->fim = novo;
    }

    printf("Elemento %d inserido na fila.\n", valor);
}

// Função para remover da fila (dequeue)
void dequeue(Fila *fila)
{
    if (fila == NULL || fila->inicio == NULL)
    {
        printf("Fila vazia. Nada para remover.\n");
        return;
    }

    No *temp = fila->inicio;
    int valor = temp->dado;
    fila->inicio = fila->inicio->ptprox;

    if (fila->inicio == NULL)
    {
        fila->fim = NULL;
    }

    free(temp);
    printf("Elemento %d removido da fila.\n", valor);
}

// ==================== PILHA (LIFO) ====================

typedef struct
{
    No *topo;
} Pilha;

// Função para inicializar pilha
Pilha *inicializarPilha()
{
    Pilha *pilha = (Pilha *)malloc(sizeof(Pilha));
    if (pilha == NULL)
    {
        printf("Erro na alocacao de memoria!\n");
        return NULL;
    }

    pilha->topo = NULL;
    return pilha;
}

// Função para imprimir pilha
void imprimirPilha(Pilha *pilha)
{
    if (pilha == NULL || pilha->topo == NULL)
    {
        printf("Pilha vazia.\n");
        return;
    }

    printf("Pilha (topo -> base): ");
    No *atual = pilha->topo;
    while (atual != NULL)
    {
        printf("%d", atual->dado);
        if (atual->ptprox != NULL)
        {
            printf(" -> ");
        }
        atual = atual->ptprox;
    }
    printf("\n");
}

// Função para inserir na pilha (push)
void push(Pilha *pilha, int valor)
{
    if (pilha == NULL)
        return;

    No *novo = (No *)malloc(sizeof(No));
    if (novo == NULL)
    {
        printf("Erro na alocacao de memoria!\n");
        return;
    }

    novo->dado = valor;
    novo->ptprox = pilha->topo;
    pilha->topo = novo;

    printf("Elemento %d inserido na pilha.\n", valor);
}

// Função para remover da pilha (pop)
void pop(Pilha *pilha)
{
    if (pilha == NULL || pilha->topo == NULL)
    {
        printf("Pilha vazia. Nada para remover.\n");
        return;
    }

    No *temp = pilha->topo;
    int valor = temp->dado;
    pilha->topo = pilha->topo->ptprox;
    free(temp);

    printf("Elemento %d removido da pilha.\n", valor);
}

// ==================== FUNÇÕES DE MENU PARA CADA ESTRUTURA ====================

void menuListaSimples()
{
    No *lista = NULL;
    int opcao, valor, pos;

    do
    {
        printf("\n=== Lista Simplesmente Encadeada Ordenada ===\n");
        printf("1 - Inserir elemento\n");
        printf("2 - Remover elemento\n");
        printf("3 - Buscar elemento\n");
        printf("4 - Voltar ao menu principal\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            printf("Digite o valor a inserir: ");
            scanf("%d", &valor);
            lista = inserirListaSimples(lista, valor);
            printf("Elemento %d inserido.\n", valor);
            imprimirListaSimples(lista);
            break;
        case 2:
            printf("Digite o valor a remover: ");
            scanf("%d", &valor);
            lista = removerListaSimples(lista, valor);
            imprimirListaSimples(lista);
            break;
        case 3:
            printf("Digite o valor a buscar: ");
            scanf("%d", &valor);
            pos = buscarListaSimples(lista, valor);
            if (pos != -1)
            {
                printf("Elemento %d encontrado na posicao %d.\n", valor, pos);
            }
            else
            {
                printf("Elemento %d nao encontrado.\n", valor);
            }
            imprimirListaSimples(lista);
            break;
        case 4:
            break;
        default:
            printf("opcao invalida!\n");
        }
    } while (opcao != 4);

    desalocarListaSimples(lista);
}

void menuListaCircular()
{
    No *lista = NULL;
    int opcao, valor, pos;

    do
    {
        printf("\n=== Lista Circular Simplesmente Encadeada Ordenada ===\n");
        printf("1 - Inserir elemento\n");
        printf("2 - Remover elemento\n");
        printf("3 - Buscar elemento\n");
        printf("4 - Voltar ao menu principal\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            printf("Digite o valor a inserir: ");
            scanf("%d", &valor);
            lista = inserirListaCircular(lista, valor);
            printf("Elemento %d inserido.\n", valor);
            imprimirListaCircular(lista);
            break;
        case 2:
            printf("Digite o valor a remover: ");
            scanf("%d", &valor);
            lista = removerListaCircular(lista, valor);
            imprimirListaCircular(lista);
            break;
        case 3:
            printf("Digite o valor a buscar: ");
            scanf("%d", &valor);
            pos = buscarListaCircular(lista, valor); // CORREÇÃO: usar buscarListaCircular
            if (pos != -1)
            {
                printf("Elemento %d encontrado na posicao %d.\n", valor, pos);
            }
            else
            {
                printf("Elemento %d nao encontrado.\n", valor);
            }
            imprimirListaCircular(lista);
            break;
        case 4:
            break;
        default:
            printf("opcao invalida!\n");
        }
    } while (opcao != 4);

    // Desalocar lista circular
    if (lista != NULL)
    {
        No *atual = lista->ptprox;
        while (atual != lista)
        {
            No *temp = atual;
            atual = atual->ptprox;
            free(temp);
        }
        free(lista);
    }
}

void menuListaDupla()
{
    NoDuplo *lista = inicializarListaDupla();
    int opcao, valor;

    if (lista == NULL)
        return;

    do
    {
        printf("\n=== Lista Duplamente Encadeada com No Cabeca ===\n");
        printf("1 - Inserir elemento\n");
        printf("2 - Remover elemento\n");
        printf("3 - Buscar elemento\n");
        printf("4 - Voltar ao menu principal\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            printf("Digite o valor a inserir: ");
            scanf("%d", &valor);
            inserirListaDupla(lista, valor);
            printf("Elemento %d inserido.\n", valor);
            imprimirListaDupla(lista);
            break;
        case 2:
            printf("Digite o valor a remover: ");
            scanf("%d", &valor);
            removerListaDupla(lista, valor);
            imprimirListaDupla(lista);
            break;
        case 3:
            printf("Digite o valor a buscar: ");
            scanf("%d", &valor);
            // Buscar na lista duplamente encadeada
            if (lista->ptprox != lista)
            {
                NoDuplo *atual = lista->ptprox;
                int pos = 0;
                int encontrado = 0;
                while (atual != lista)
                {
                    if (atual->dado == valor)
                    {
                        printf("Elemento %d encontrado na posicao %d.\n", valor, pos);
                        encontrado = 1;
                        break;
                    }
                    atual = atual->ptprox;
                    pos++;
                }
                if (!encontrado)
                {
                    printf("Elemento %d nao encontrado.\n", valor);
                }
            }
            else
            {
                printf("Elemento %d nao encontrado.\n", valor);
            }
            imprimirListaDupla(lista);
            break;
        case 4:
            break;
        default:
            printf("opcao invalida!\n");
        }
    } while (opcao != 4);

    // Desalocar lista duplamente encadeada
    while (lista->ptprox != lista)
    {
        NoDuplo *temp = lista->ptprox;
        lista->ptprox = temp->ptprox;
        temp->ptprox->ptant = lista;
        free(temp);
    }
    free(lista);
}

void menuFila()
{
    Fila *fila = inicializarFila();
    int opcao, valor;

    if (fila == NULL)
        return;

    do
    {
        printf("\n=== Fila (FIFO) ===\n");
        printf("1 - Inserir elemento (enqueue)\n");
        printf("2 - Remover elemento (dequeue)\n");
        printf("3 - Voltar ao menu principal\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            printf("Digite o valor a inserir: ");
            scanf("%d", &valor);
            enqueue(fila, valor);
            imprimirFila(fila);
            break;
        case 2:
            dequeue(fila);
            imprimirFila(fila);
            break;
        case 3:
            break;
        default:
            printf("opcao invalida!\n");
        }
    } while (opcao != 3);

    // Desalocar fila
    while (fila->inicio != NULL)
    {
        No *temp = fila->inicio;
        fila->inicio = fila->inicio->ptprox;
        free(temp);
    }
    free(fila);
}

void menuPilha()
{
    Pilha *pilha = inicializarPilha();
    int opcao, valor;

    if (pilha == NULL)
        return;

    do
    {
        printf("\n=== Pilha (LIFO) ===\n");
        printf("1 - Inserir elemento (push)\n");
        printf("2 - Remover elemento (pop)\n");
        printf("3 - Voltar ao menu principal\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            printf("Digite o valor a inserir: ");
            scanf("%d", &valor);
            push(pilha, valor);
            imprimirPilha(pilha);
            break;
        case 2:
            pop(pilha);
            imprimirPilha(pilha);
            break;
        case 3:
            break;
        default:
            printf("opcao invalida!\n");
        }
    } while (opcao != 3);

    // Desalocar pilha
    while (pilha->topo != NULL)
    {
        No *temp = pilha->topo;
        pilha->topo = pilha->topo->ptprox;
        free(temp);
    }
    free(pilha);
}

// ==================== FUNÇÃO PRINCIPAL ====================

int main()
{
    char escolha;

    do
    {
        int opcao;

        printf("\n## Manipulacao de Listas, Pilhas e Filas ##\n\n");
        printf("1 - Lista Simplesmente Encadeada Ordenada\n");
        printf("2 - Lista Circular Simplesmente Encadeada Ordenada\n");
        printf("3 - Lista Duplamente Encadeada com No Cabeca\n");
        printf("4 - Fila (FIFO)\n");
        printf("5 - Pilha (LIFO)\n");
        printf("6 - Sair\n");
        printf("\nEscolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            menuListaSimples();
            break;
        case 2:
            menuListaCircular();
            break;
        case 3:
            menuListaDupla();
            break;
        case 4:
            menuFila();
            break;
        case 5:
            menuPilha();
            break;
        case 6:
            printf("\nEncerrando programa...\n");
            return 0;
        default:
            printf("\nOpcao invalida! Tente novamente.\n");
            break;
        }

        printf("\nDeseja fazer outra manipulacao? (s/n): ");
        scanf(" %c", &escolha);

    } while (escolha == 'S' || escolha == 's');

    printf("\n\nFim do programa.\n\n");
    return 0;
}