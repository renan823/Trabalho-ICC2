/**
 * Código para resolver o problema da mochila com o método da força bruta
 * 
 * @author Augusto Fernandes Ildefonso
 * @date 17/09/2024
 */
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define TAM_MAX 1000000 // Definindo o tamanho máximo da mochila

/**
 * Protótipos das funções
 */
int* forca_bruta(int peso[], int valor[], int N, int W, int mochila[]);
void zera_vetor(int** aux, int N);
void copia_vetor(int** mochila, int** aux, int N);

/**
 * Função que zera o vetor, é usada para gerar todas as possibilidades de combinações dos itens
 * 
 * @param aux Ponteiro para o vetor auxiliar
 * @param N Tamanho da mochila
 */
void zera_vetor(int** aux, int N){
    for(int i = 0; i < N; i++){
        (*aux)[i] = 0; 
    }
}

/**
 * Função que copia o vetor aux para o vetor mochila
 * 
 * @param mochila Ponteiro para o vetor mochila
 * @param aux Ponteiro para o vetor aux
 * @param N Tamanho da mochila
 */
void copia_vetor(int** mochila, int** aux, int N){
    for(int i = 0; i < N; i++){
        (*mochila)[i] = (*aux)[i];
    }
}

/**
 * Função que resolve o problema da mochila usando o método da força dupla
 * 
 * @param peso Vetor que contém os pesos dos itens
 * @param valor Vetor que contém os valores dos itens
 * @param N Tamanho da mochila
 * @param W Peso máximo que a mochila suporta
 * @param mochila Vetor que representa a mochila
 * 
 * @return Retorna a mochila que contém o maior valor, dentro do peso máximo
 */
int* forca_bruta(int peso[], int valor[], int N, int W, int mochila[]){
    int total_combinacoes = 1 << N;
    int peso_atual = 0, valor_atual = 0, maior_valor = 0, peso_maior_valor;
    int* aux;

    aux = (int*) malloc(sizeof(int) * N);

    for(int i = 0; i < total_combinacoes; i++){
        zera_vetor(&aux, N);
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

    scanf("%d %d", &N, &W);

    mochila = (int*) calloc(sizeof(int), N);

    for(int i = 0; i < N; i++){
        scanf("%d %d", &peso[i], &valor[i]);
    }

    //inicar contagem
    clock_t inicio = clock();

    mochila = forca_bruta(peso, valor, N, W, mochila);

    //fim da execução
    clock_t fim = clock();

    printf("Tempo decorrido: %lf segundos\n", (double)(fim - inicio) / CLOCKS_PER_SEC);

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