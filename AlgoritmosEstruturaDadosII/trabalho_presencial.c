#include<stdlib.h>
#include<stdio.h>

typedef struct No{
    int valor;
    struct No* prox;
} No;

No* aloca(No* ptlista){
    No* novo;
    novo = malloc(sizeof(No));
    novo->prox = NULL;
    return novo;
}

int main(){
    
    int opcao, valor;
    No* ptlista;
    char continuar;

    ptlista = CarregarArquivo("r");
    
    scanf("%d", &opcao);
    do{
     switch(opcao){
        case 1: 
            scanf("%d", &valor);
            Inserir(ptlista, valor);
            break;
        case 2: 
            scanf("%d", &valor);
            Remover(ptlista, valor);
            break;
        case 3:
            scanf("%d", &valor);
            Buscar(ptlista, valor);
            break;
        case 4: 
            desaloca(ptlista);
            break;
        default:
            printf("\nopcao invalida\n");
            break;
     }
    } while(continuar == 'S' || 's');

    

    return 0;
}
