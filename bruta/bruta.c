#include <stdio.h>
#include <stdlib.h>

int main(void){
    int N, W, peso, valor;
    int** lista_itens, **mochila;

    printf("Tamanho da mochila: ");
    scanf("%d", &N);
    printf("\n\nPeso máximo: ");
    scanf("%d", &W);

    for(int i = 0; i < N; i++){
        printf("\nPeso | Valor\n");
        scanf("%d %d", &peso, &valor);
        printf("\n");

        mochila[0][i] = lista_itens[0][i] = peso;
        mochila[1][i] = lista_itens[1][i] = valor;
    }
        
    for (int i = 0; i < N; i++){
        
    }
    
    
    return(0);
}