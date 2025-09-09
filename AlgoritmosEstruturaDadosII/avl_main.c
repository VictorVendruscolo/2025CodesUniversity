/*
 * Programa de Árvore AVL em C
 * Implementa todas as operações solicitadas:
 * - Busca, inserção e remoção com rotações AVL
 * - Impressão em pré-ordem, em ordem e pós-ordem
 * - Leitura/gravação em arquivo binário
 * - Desalocação da árvore
 * - Interface modo texto
 * 
 * Compilação: gcc -o avl main.c -lncurses -Wall -Wextra -pedantic
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "print-avl.h"

/* Estrutura do nó na memória */
struct s_no {
    int32_t chave:28;
    int32_t bal:2;
    int32_t reservado:2;
    struct s_no* esq;
    struct s_no* dir;
};

/* Estrutura do nó para arquivo */
struct s_arq_no {
    int32_t chave:28;
    int32_t bal:2;
    uint32_t esq:1;
    uint32_t dir:1;
};

/* Ponteiro para a raiz da árvore */
struct s_no* raiz = NULL;

/* Protótipos das funções */
int altura(struct s_no* no);
int calcular_balanco(struct s_no* no);
struct s_no* rotacao_direita(struct s_no* y);
struct s_no* rotacao_esquerda(struct s_no* x);
struct s_no* inserir(struct s_no* no, int chave);
struct s_no* buscar(struct s_no* no, int chave);
struct s_no* remover(struct s_no* no, int chave);
struct s_no* min_valor_no(struct s_no* no);
void pre_ordem(struct s_no* no);
void em_ordem(struct s_no* no);
void pos_ordem(struct s_no* no);
void salvar_arvore(struct s_no* no, FILE* arquivo);
struct s_no* carregar_arvore(FILE* arquivo);
void desalocar_arvore(struct s_no* no);
void imprimir_menu();
void processar_opcao(int opcao);
int ler_inteiro(const char* prompt);

/* Função para calcular altura do nó */
int altura(struct s_no* no) {
    if (no == NULL) {
        return 0;
    }

    int altura_esq = altura(no->esq);
    int altura_dir = altura(no->dir);

    return 1 + (altura_esq > altura_dir ? altura_esq : altura_dir);
}

/* Função para calcular fator de balanceamento */
int calcular_balanco(struct s_no* no) {
    if (no == NULL) {
        return 0;
    }
    return altura(no->esq) - altura(no->dir);
}

/* Rotação simples à direita */
struct s_no* rotacao_direita(struct s_no* y) {
    struct s_no* x = y->esq;
    struct s_no* T2 = x->dir;

    /* Realizar rotação */
    x->dir = y;
    y->esq = T2;

    /* Atualizar fatores de balanceamento */
    y->bal = calcular_balanco(y);
    x->bal = calcular_balanco(x);

    /* Retornar nova raiz */
    return x;
}

/* Rotação simples à esquerda */
struct s_no* rotacao_esquerda(struct s_no* x) {
    struct s_no* y = x->dir;
    struct s_no* T2 = y->esq;

    /* Realizar rotação */
    y->esq = x;
    x->dir = T2;

    /* Atualizar fatores de balanceamento */
    x->bal = calcular_balanco(x);
    y->bal = calcular_balanco(y);

    /* Retornar nova raiz */
    return y;
}

/* Função para inserir um nó na árvore AVL */
struct s_no* inserir(struct s_no* no, int chave) {
    /* 1. Inserção normal BST */
    if (no == NULL) {
        struct s_no* novo_no = malloc(sizeof(struct s_no));
        if (novo_no == NULL) {
            printf("Erro: Falha na alocação de memória!\n");
            return NULL;
        }
        novo_no->chave = chave;
        novo_no->esq = NULL;
        novo_no->dir = NULL;
        novo_no->bal = 0;
        novo_no->reservado = 0;
        return novo_no;
    }

    if (chave < no->chave) {
        no->esq = inserir(no->esq, chave);
    } else if (chave > no->chave) {
        no->dir = inserir(no->dir, chave);
    } else {
        /* Chaves duplicadas não são permitidas */
        return no;
    }

    /* 2. Atualizar fator de balanceamento do nó atual */
    no->bal = calcular_balanco(no);

    /* 3. Verificar se o nó ficou desbalanceado */
    int balanco = no->bal;

    /* Caso Esquerda-Esquerda */
    if (balanco > 1 && chave < no->esq->chave) {
        return rotacao_direita(no);
    }

    /* Caso Direita-Direita */
    if (balanco < -1 && chave > no->dir->chave) {
        return rotacao_esquerda(no);
    }

    /* Caso Esquerda-Direita */
    if (balanco > 1 && chave > no->esq->chave) {
        no->esq = rotacao_esquerda(no->esq);
        return rotacao_direita(no);
    }

    /* Caso Direita-Esquerda */
    if (balanco < -1 && chave < no->dir->chave) {
        no->dir = rotacao_direita(no->dir);
        return rotacao_esquerda(no);
    }

    /* Retornar o nó (inalterado) */
    return no;
}

/* Função para buscar uma chave na árvore */
struct s_no* buscar(struct s_no* no, int chave) {
    if (no == NULL || no->chave == chave) {
        return no;
    }

    if (chave < no->chave) {
        return buscar(no->esq, chave);
    }

    return buscar(no->dir, chave);
}

/* Função para encontrar o nó com valor mínimo */
struct s_no* min_valor_no(struct s_no* no) {
    struct s_no* atual = no;

    /* Percorrer para a esquerda até encontrar o menor */
    while (atual->esq != NULL) {
        atual = atual->esq;
    }

    return atual;
}

/* Função para remover um nó da árvore AVL */
struct s_no* remover(struct s_no* no, int chave) {
    /* PASSO 1: REALIZAR REMOÇÃO BST PADRÃO */
    if (no == NULL) {
        return no;
    }

    /* Se a chave for menor que a chave do nó, está na subárvore esquerda */
    if (chave < no->chave) {
        no->esq = remover(no->esq, chave);
    }
    /* Se a chave for maior que a chave do nó, está na subárvore direita */
    else if (chave > no->chave) {
        no->dir = remover(no->dir, chave);
    }
    /* Se a chave for igual à chave do nó, este é o nó a ser removido */
    else {
        /* Nó com apenas um filho ou nenhum filho */
        if ((no->esq == NULL) || (no->dir == NULL)) {
            struct s_no* temp = no->esq ? no->esq : no->dir;

            /* Caso sem filhos */
            if (temp == NULL) {
                temp = no;
                no = NULL;
            } else {
                /* Caso com um filho */
                *no = *temp; /* Copiar conteúdo do filho não-nulo */
            }
            free(temp);
        } else {
            /* Nó com dois filhos: obter o sucessor em ordem 
               (menor na subárvore direita) */
            struct s_no* temp = min_valor_no(no->dir);

            /* Copiar dados do sucessor em ordem para este nó */
            no->chave = temp->chave;

            /* Remover o sucessor em ordem */
            no->dir = remover(no->dir, temp->chave);
        }
    }

    /* Se a árvore tinha apenas um nó, retornar */
    if (no == NULL) {
        return no;
    }

    /* PASSO 2: ATUALIZAR FATOR DE BALANCEAMENTO DO NÓ ATUAL */
    no->bal = calcular_balanco(no);

    /* PASSO 3: VERIFICAR SE ESTE NÓ FICOU DESBALANCEADO */
    int balanco = no->bal;

    /* Caso Esquerda-Esquerda */
    if (balanco > 1 && calcular_balanco(no->esq) >= 0) {
        return rotacao_direita(no);
    }

    /* Caso Esquerda-Direita */
    if (balanco > 1 && calcular_balanco(no->esq) < 0) {
        no->esq = rotacao_esquerda(no->esq);
        return rotacao_direita(no);
    }

    /* Caso Direita-Direita */
    if (balanco < -1 && calcular_balanco(no->dir) <= 0) {
        return rotacao_esquerda(no);
    }

    /* Caso Direita-Esquerda */
    if (balanco < -1 && calcular_balanco(no->dir) > 0) {
        no->dir = rotacao_direita(no->dir);
        return rotacao_esquerda(no);
    }

    /* Retornar o nó (possivelmente alterado) */
    return no;
}

/* Impressão em pré-ordem */
void pre_ordem(struct s_no* no) {
    if (no != NULL) {
        printf("Chave: %d, Balanço: %d\n", no->chave, no->bal);
        pre_ordem(no->esq);
        pre_ordem(no->dir);
    }
}

/* Impressão em ordem simétrica */
void em_ordem(struct s_no* no) {
    if (no != NULL) {
        em_ordem(no->esq);
        printf("Chave: %d, Balanço: %d\n", no->chave, no->bal);
        em_ordem(no->dir);
    }
}

/* Impressão em pós-ordem */
void pos_ordem(struct s_no* no) {
    if (no != NULL) {
        pos_ordem(no->esq);
        pos_ordem(no->dir);
        printf("Chave: %d, Balanço: %d\n", no->chave, no->bal);
    }
}

/* Salvar árvore em arquivo binário (pré-ordem) */
void salvar_arvore(struct s_no* no, FILE* arquivo) {
    if (no == NULL) {
        /* Escrever marcador para nó nulo */
        struct s_arq_no nulo = {0, 0, 0, 0};
        fwrite(&nulo, sizeof(struct s_arq_no), 1, arquivo);
        return;
    }

    /* Criar estrutura para arquivo */
    struct s_arq_no arq_no;
    arq_no.chave = no->chave;
    arq_no.bal = no->bal;
    arq_no.esq = (no->esq != NULL) ? 1 : 0;
    arq_no.dir = (no->dir != NULL) ? 1 : 0;

    /* Escrever nó atual */
    fwrite(&arq_no, sizeof(struct s_arq_no), 1, arquivo);

    /* Recursivamente salvar subárvores */
    salvar_arvore(no->esq, arquivo);
    salvar_arvore(no->dir, arquivo);
}

/* Carregar árvore de arquivo binário */
struct s_no* carregar_arvore(FILE* arquivo) {
    struct s_arq_no arq_no;

    /* Ler próximo nó do arquivo */
    if (fread(&arq_no, sizeof(struct s_arq_no), 1, arquivo) != 1) {
        return NULL;
    }

    /* Verificar se é nó nulo */
    if (arq_no.chave == 0 && arq_no.bal == 0 && 
        arq_no.esq == 0 && arq_no.dir == 0) {
        return NULL;
    }

    /* Criar novo nó */
    struct s_no* no = malloc(sizeof(struct s_no));
    if (no == NULL) {
        printf("Erro: Falha na alocação de memória!\n");
        return NULL;
    }

    no->chave = arq_no.chave;
    no->bal = arq_no.bal;
    no->reservado = 0;

    /* Recursivamente carregar subárvores */
    if (arq_no.esq) {
        no->esq = carregar_arvore(arquivo);
    } else {
        no->esq = NULL;
    }

    if (arq_no.dir) {
        no->dir = carregar_arvore(arquivo);
    } else {
        no->dir = NULL;
    }

    return no;
}

/* Desalocar toda a árvore */
void desalocar_arvore(struct s_no* no) {
    if (no != NULL) {
        desalocar_arvore(no->esq);
        desalocar_arvore(no->dir);
        free(no);
    }
}

/* Função auxiliar para ler inteiro com validação */
int ler_inteiro(const char* prompt) {
    int valor;
    char buffer[100];

    while (1) {
        printf("%s", prompt);
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            if (sscanf(buffer, "%d", &valor) == 1) {
                return valor;
            }
        }
        printf("Entrada inválida! Digite um número inteiro.\n");
    }
}

/* Imprimir menu principal */
void imprimir_menu() {
    printf("\n=== ÁRVORE AVL - MENU PRINCIPAL ===\n");
    printf("1.  Inserir chave\n");
    printf("2.  Buscar chave\n");
    printf("3.  Remover chave\n");
    printf("4.  Imprimir pré-ordem\n");
    printf("5.  Imprimir em ordem\n");
    printf("6.  Imprimir pós-ordem\n");
    printf("7.  Visualizar árvore (ncurses)\n");
    printf("8.  Salvar árvore em arquivo\n");
    printf("9.  Carregar árvore de arquivo\n");
    printf("10. Nova árvore (limpar atual)\n");
    printf("0.  Sair\n");
    printf("=====================================\n");
}

/* Processar opção escolhida pelo usuário */
void processar_opcao(int opcao) {
    int chave;
    struct s_no* resultado;
    FILE* arquivo;
    char nome_arquivo[256];

    switch (opcao) {
        case 1: /* Inserir */
            chave = ler_inteiro("Digite a chave a inserir: ");
            raiz = inserir(raiz, chave);
            printf("Chave %d inserida com sucesso!\n", chave);
            break;

        case 2: /* Buscar */
            chave = ler_inteiro("Digite a chave a buscar: ");
            resultado = buscar(raiz, chave);
            if (resultado != NULL) {
                printf("Chave %d encontrada! Balanço: %d\n", 
                       resultado->chave, resultado->bal);
            } else {
                printf("Chave %d não encontrada.\n", chave);
            }
            break;

        case 3: /* Remover */
            chave = ler_inteiro("Digite a chave a remover: ");
            resultado = buscar(raiz, chave);
            if (resultado != NULL) {
                raiz = remover(raiz, chave);
                printf("Chave %d removida com sucesso!\n", chave);
            } else {
                printf("Chave %d não encontrada.\n", chave);
            }
            break;

        case 4: /* Pré-ordem */
            printf("\n=== IMPRESSÃO PRÉ-ORDEM ===\n");
            if (raiz == NULL) {
                printf("Árvore vazia!\n");
            } else {
                pre_ordem(raiz);
            }
            break;

        case 5: /* Em ordem */
            printf("\n=== IMPRESSÃO EM ORDEM ===\n");
            if (raiz == NULL) {
                printf("Árvore vazia!\n");
            } else {
                em_ordem(raiz);
            }
            break;

        case 6: /* Pós-ordem */
            printf("\n=== IMPRESSÃO PÓS-ORDEM ===\n");
            if (raiz == NULL) {
                printf("Árvore vazia!\n");
            } else {
                pos_ordem(raiz);
            }
            break;

        case 7: /* Visualizar com ncurses */
            printf("Visualizando árvore...\n");
            imprime_arvore(raiz);
            break;

        case 8: /* Salvar */
            printf("Digite o nome do arquivo: ");
            if (fgets(nome_arquivo, sizeof(nome_arquivo), stdin) != NULL) {
                /* Remover quebra de linha */
                nome_arquivo[strcspn(nome_arquivo, "\n")] = 0;

                arquivo = fopen(nome_arquivo, "wb");
                if (arquivo != NULL) {
                    salvar_arvore(raiz, arquivo);
                    fclose(arquivo);
                    printf("Árvore salva em '%s' com sucesso!\n", nome_arquivo);
                } else {
                    printf("Erro: Não foi possível abrir o arquivo para escrita.\n");
                }
            }
            break;

        case 9: /* Carregar */
            printf("Digite o nome do arquivo: ");
            if (fgets(nome_arquivo, sizeof(nome_arquivo), stdin) != NULL) {
                /* Remover quebra de linha */
                nome_arquivo[strcspn(nome_arquivo, "\n")] = 0;

                arquivo = fopen(nome_arquivo, "rb");
                if (arquivo != NULL) {
                    /* Desalocar árvore atual */
                    desalocar_arvore(raiz);

                    /* Carregar nova árvore */
                    raiz = carregar_arvore(arquivo);
                    fclose(arquivo);
                    printf("Árvore carregada de '%s' com sucesso!\n", nome_arquivo);
                } else {
                    printf("Erro: Não foi possível abrir o arquivo para leitura.\n");
                }
            }
            break;

        case 10: /* Nova árvore */
            desalocar_arvore(raiz);
            raiz = NULL;
            printf("Nova árvore criada (árvore anterior desalocada).\n");
            break;

        case 0: /* Sair */
            printf("Encerrando programa...\n");
            desalocar_arvore(raiz);
            break;

        default:
            printf("Opção inválida! Tente novamente.\n");
    }
}

/* Função principal */
int main() {
    int opcao;

    printf("=== PROGRAMA DE ÁRVORE AVL ===\n");
    printf("Desenvolvido seguindo as especificações acadêmicas\n");
    printf("Suporta todas as operações AVL com interface interativa\n");

    do {
        imprimir_menu();
        opcao = ler_inteiro("Escolha uma opção: ");

        processar_opcao(opcao);

        /* Após cada operação (exceto sair), mostrar árvore automaticamente */
        if (opcao != 0 && opcao >= 1 && opcao <= 10) {
            if (raiz != NULL) {
                printf("\n--- Estado atual da árvore ---\n");
                imprime_arvore(raiz);
            }
        }

    } while (opcao != 0);

    return 0;
}
