/*
 * Programa de Árvore Binária de Busca com suporte a:
 * Inserção, remoção, busca, menor/maior, predecessor/sucessor
 * Impressão em pré-ordem, in-ordem e pós-ordem
 * Leitura/Gravação em arquivo binário usando struct s_arq_no
 *
 * Compilar com:
 * gcc -Wall -Wextra -pedantic -o arvore arvore.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
// #include <string.h> // Não utilizado

#define FILENAME "arvore.bin"

// Estrutura para gravação em arquivo, conforme especificado.
// Usa bit-fields para ocupar exatamente 4 bytes.
struct s_arq_no {
    int32_t chave:30;
    uint32_t esq:1;
    uint32_t dir:1;
};

// Estrutura do nó da árvore em memória.
typedef struct No {
    int chave;
    struct No *esq, *dir;
} No;

// Protótipos das funções
No* novo_no(int chave);
No* inserir(No* raiz, int chave);
No* buscar(No* raiz, int chave);
No* menor(No* raiz);
No* maior(No* raiz);
No* sucessor(No* raiz, int chave);
No* predecessor(No* raiz, int chave);
No* remover(No* raiz, int chave);
void pre_ordem(No* r);
void em_ordem(No* r);
void pos_ordem(No* r);
void salvar_arq(FILE* f, No* r);
No* ler_arq(FILE* f);
void liberar(No* r);
void menu();
void imprimir_submenu(No* raiz);

// Função para criar novo nó
No* novo_no(int chave) {
    No* no = malloc(sizeof(No));
    if (!no) {
        perror("Falha na alocação de memória (malloc)");
        exit(EXIT_FAILURE);
    }
    no->chave = chave;
    no->esq = no->dir = NULL;
    return no;
}

// Inserção em Árvore Binária de Busca
No* inserir(No* raiz, int chave) {
    if (!raiz) return novo_no(chave);
    if (chave < raiz->chave)
        raiz->esq = inserir(raiz->esq, chave);
    else if (chave > raiz->chave)
        raiz->dir = inserir(raiz->dir, chave);
    return raiz;
}

// Busca por uma chave
No* buscar(No* raiz, int chave) {
    if (!raiz || raiz->chave == chave) return raiz;
    if (chave < raiz->chave)
        return buscar(raiz->esq, chave);
    else
        return buscar(raiz->dir, chave);
}

// Encontra a menor chave (nó mais à esquerda)
No* menor(No* raiz) {
    No* atual = raiz;
    while (atual && atual->esq)
        atual = atual->esq;
    return atual;
}

// Encontra a maior chave (nó mais à direita)
No* maior(No* raiz) {
    No* atual = raiz;
    while (atual && atual->dir)
        atual = atual->dir;
    return atual;
}

// Encontra o sucessor em-ordem de uma chave
No* sucessor(No* raiz, int chave) {
    No* no_chave = buscar(raiz, chave);
    if (!no_chave) return NULL; // Chave não existe na árvore

    if (no_chave->dir) {
        return menor(no_chave->dir);
    }

    No *succ = NULL;
    No *ancestral = raiz;
    while(ancestral != no_chave) {
        if(no_chave->chave < ancestral->chave) {
            succ = ancestral;
            ancestral = ancestral->esq;
        } else {
            ancestral = ancestral->dir;
        }
    }
    return succ;
}


// Encontra o predecessor em-ordem de uma chave
No* predecessor(No* raiz, int chave) {
    No* no_chave = buscar(raiz, chave);
    if (!no_chave) return NULL; // Chave não existe na árvore

    if (no_chave->esq) {
        return maior(no_chave->esq);
    }
    
    No *pred = NULL;
    No *ancestral = raiz;
    while(ancestral != no_chave) {
        if(no_chave->chave > ancestral->chave) {
            pred = ancestral;
            ancestral = ancestral->dir;
        } else {
            ancestral = ancestral->esq;
        }
    }
    return pred;
}


// Remoção de um nó
No* remover(No* raiz, int chave) {
    if (!raiz) return NULL;
    if (chave < raiz->chave) {
        raiz->esq = remover(raiz->esq, chave);
    } else if (chave > raiz->chave) {
        raiz->dir = remover(raiz->dir, chave);
    } else {
        // Nó com um ou nenhum filho
        if (!raiz->esq) {
            No* temp = raiz->dir;
            free(raiz);
            return temp;
        } else if (!raiz->dir) {
            No* temp = raiz->esq;
            free(raiz);
            return temp;
        }
        // Nó com dois filhos: pega o sucessor em-ordem
        No* temp = menor(raiz->dir);
        raiz->chave = temp->chave;
        raiz->dir = remover(raiz->dir, temp->chave);
    }
    return raiz;
}

// Impressão em Pré-ordem
void pre_ordem(No* r) {
    if (!r) return;
    printf("%d ", r->chave);
    pre_ordem(r->esq);
    pre_ordem(r->dir);
}

// Impressão Em-ordem (simétrica)
void em_ordem(No* r) {
    if (!r) return;
    em_ordem(r->esq);
    printf("%d ", r->chave);
    em_ordem(r->dir);
}

// Impressão em Pós-ordem
void pos_ordem(No* r) {
    if (!r) return;
    pos_ordem(r->esq);
    pos_ordem(r->dir);
    printf("%d ", r->chave);
}

// Gravação da árvore no arquivo em pré-ordem
void salvar_arq(FILE* f, No* r) {
    if (!r) return;

    struct s_arq_no reg;
    reg.chave = r->chave;
    reg.esq = (r->esq != NULL);
    reg.dir = (r->dir != NULL);

    fwrite(&reg, sizeof(struct s_arq_no), 1, f);

    salvar_arq(f, r->esq);
    salvar_arq(f, r->dir);
}

// Leitura da árvore a partir de arquivo binário (reconstrução pré-ordem)
No* ler_arq(FILE* f) {
    struct s_arq_no reg;
    // Tenta ler um registro do arquivo
    if (fread(&reg, sizeof(struct s_arq_no), 1, f) != 1) {
        return NULL; // Fim de arquivo ou erro de leitura
    }

    No* r = novo_no(reg.chave);
    if (reg.esq) {
        r->esq = ler_arq(f);
    }
    if (reg.dir) {
        r->dir = ler_arq(f);
    }
    return r;
}

// Liberação da memória da árvore
void liberar(No* r) {
    if (!r) return;
    liberar(r->esq);
    liberar(r->dir);
    free(r);
}

// Exibe o menu principal
void menu() {
    printf("\n--- MENU DE OPERACOES ---\n");
    printf("1. Inserir chave\n");
    printf("2. Remover chave\n");
    printf("3. Buscar chave\n");
    printf("4. Encontrar Menor e Maior chave\n");
    printf("5. Encontrar Sucessor e Predecessor\n");
    printf("6. Imprimir arvore\n");
    printf("7. Salvar arvore em arquivo\n");
    printf("8. Carregar arvore de arquivo\n");
    printf("9. Sair\n");
    printf("Escolha uma opcao: ");
}

// Submenu para os tipos de impressão
void imprimir_submenu(No* raiz) {
    if (!raiz) {
        printf("Arvore vazia.\n");
        return;
    }
    int op;
    printf("\n--- TIPO DE IMPRESSAO ---\n");
    printf("1. Pre-ordem\n2. Em-ordem\n3. Pos-ordem\nEscolha: ");
    if (scanf("%d", &op) != 1) {
        while(getchar()!='\n'); // Limpa buffer de entrada
        op = 0; // Opção inválida
    }

    printf("Resultado: ");
    switch (op) {
        case 1: pre_ordem(raiz); break;
        case 2: em_ordem(raiz); break;
        case 3: pos_ordem(raiz); break;
        default: printf("Opcao invalida.\n");
    }
    printf("\n");
}


int main(void) {
    No* raiz = NULL;
    int op, x;

    do {
        menu();
        if (scanf("%d", &op) != 1) {
            printf("Entrada invalida. Por favor, insira um numero.\n");
            while(getchar()!='\n'); // Limpa o buffer de entrada
            op = 0; // Força a continuação do loop
            continue;
        }


        switch (op) {
            case 1:
                printf("Digite a chave a ser inserida: ");
                scanf("%d", &x);
                raiz = inserir(raiz, x);
                printf("Chave %d inserida.\n", x);
                break;

            case 2:
                if (!raiz) {
                    printf("Arvore vazia.\n");
                    break;
                }
                printf("Digite a chave a ser removida: ");
                scanf("%d", &x);
                if(buscar(raiz, x)){
                    raiz = remover(raiz, x);
                    printf("Chave %d removida.\n", x);
                } else {
                    printf("Chave %d nao encontrada na arvore.\n", x);
                }
                break;

            case 3:
                if (!raiz) {
                    printf("Arvore vazia.\n");
                    break;
                }
                printf("Digite a chave a ser buscada: ");
                scanf("%d", &x);
                printf(buscar(raiz, x) ? "Chave %d encontrada.\n" : "Chave %d nao encontrada.\n", x);
                break;

            case 4:
                if (!raiz) {
                    printf("Arvore vazia.\n");
                } else {
                    printf("Menor chave: %d\nMaior chave: %d\n", menor(raiz)->chave, maior(raiz)->chave);
                }
                break;

            case 5:
                if (!raiz) {
                    printf("Arvore vazia.\n");
                    break;
                }
                printf("Digite a chave para encontrar sucessor/predecessor: ");
                scanf("%d", &x);
                
                No* pred = predecessor(raiz, x);
                No* succ = sucessor(raiz, x);

                if(!buscar(raiz, x)) {
                    printf("Chave %d nao existe na arvore.\n", x);
                    break;
                }

                if (pred) printf("Predecessor de %d: %d\n", x, pred->chave);
                else printf("A chave %d nao possui predecessor.\n", x);

                if (succ) printf("Sucessor de %d: %d\n", x, succ->chave);
                else printf("A chave %d nao possui sucessor.\n", x);
                break;

            case 6:
                imprimir_submenu(raiz);
                break;

            case 7: {
                FILE* f = fopen(FILENAME, "wb");
                if (!f) {
                    perror("Nao foi possivel abrir o arquivo para escrita");
                    break;
                }
                salvar_arq(f, raiz);
                fclose(f);
                printf("Arvore salva com sucesso em '%s'.\n", FILENAME);
                break;
            }

            case 8: {
                FILE* f = fopen(FILENAME, "rb");
                if (!f) {
                    printf("Arquivo '%s' nao encontrado ou nao pode ser lido. A arvore permanece vazia.\n", FILENAME);
                    raiz = NULL; // Garante que a árvore está vazia
                    break;
                }
                liberar(raiz); // Libera a árvore atual antes de carregar uma nova
                raiz = ler_arq(f);
                fclose(f);
                printf("Arvore carregada com sucesso de '%s'.\n", FILENAME);
                break;
            }

            case 9:
                liberar(raiz);
                printf("Saindo do programa. Memoria liberada.\n");
                break;

            default:
                printf("Opcao invalida. Tente novamente.\n");
                break;
        }
    } while (op != 9);

    return 0;
}