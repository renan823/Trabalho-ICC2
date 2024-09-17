#include <stdio.h>
#include <stdlib.h>

#define TAM_MAX 1000000

int* forca_bruta(int peso[], int valor[], int N, int W, int mochila[]);
void inicia_vetor(int** aux, int N);
void copia_vetor(int** mochila, int** aux, int N);

void inicia_vetor(int** aux, int N){
    for(int i = 0; i < N; i++){
        (*aux)[i] = 0; 
    }
}

void copia_vetor(int** mochila, int** aux, int N){
    for(int i = 0; i < N; i++){
        (*mochila)[i] = (*aux)[i];
    }
}

int* forca_bruta(int peso[], int valor[], int N, int W, int mochila[]){
    int total_combinacoes = 1 << N;
    int peso_atual = 0, valor_atual = 0, maior_valor = 0, peso_maior_valor;
    int* aux;

    aux = (int*) malloc(sizeof(int) * N);

    for(int i = 0; i < total_combinacoes; i++){
        inicia_vetor(&aux, N);
        peso_atual = 0;
        valor_atual = 0;
        for(int j = 0; j < N; j++){
            if(i & (1 << j)){
                peso_atual += peso[j];
                valor_atual += valor[j];
                aux[j] = 1;
            }
        }

        if((peso_atual <= W) && (valor_atual > maior_valor)){
            maior_valor = valor_atual;
            peso_maior_valor = peso_atual;
            copia_vetor(&mochila, &aux, N);
        }
    }

    printf("\n\nValor total: %d\nPeso atual: %d\n", maior_valor, peso_maior_valor);
    return mochila;
}

int main(void){
    int N, W;
    int peso[TAM_MAX], valor[TAM_MAX], *mochila;

    printf("Tamanho da mochila: ");
    scanf("%d", &N);
    printf("Peso máximo da mochila: ");
    scanf("%d", &W);

    mochila = (int*) malloc(sizeof(int)*N);

    for(int i = 0; i < N; i++){
        printf("\nPeso %d: ", i);
        scanf("%d", &peso[i]);
        printf("Valor %d: ", i);
        scanf("%d", &valor[i]);
    }

    inicia_vetor(&mochila, N);

    mochila = forca_bruta(peso, valor, N, W, mochila);

    printf("Mochila: (");
    for(int i = 0; i < N; i++){
        printf("%d", mochila[i]);
        if(i != N-1){
            printf(", ");
        }
    }
    printf(")\n");

    
    return(0);
}