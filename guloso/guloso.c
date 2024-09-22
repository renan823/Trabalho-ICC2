/**
 * Código para resolver o problema da mochila usando programação dinâmica
 * 
 * @author Renan Trofino Silva
 * @date 20/09/2024
*/

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct item {
    int id;
    int valor;
    int peso;
} ITEM;

void bubble_sort(ITEM items[], int n) {
	ITEM aux;
	int trocas = 1;
	
	for (int i = 0; i < n && trocas > 0; i++) {
		trocas = 0;
		for (int j = 0; j < n-1-i; j++) {
            float valor1 = (float) items[j].valor/items[j].peso;
            float valor2 = (float) items[j+1].valor/items[j+1].peso;

			if (valor1 < valor2) {
				aux = items[j];
				items[j] = items[j+1];
				items[j+1] = aux;
				trocas++;
			}
		}
	}
}

/*
O algoritmo guloso tenta encontrar a melhor solução local.
Nesse caso, irá analisar a importância de cada objeto.
Ordenando o vetor de items pela importância.
Enquanto a mochila estiver vazia, coloque items.
E assim sucessivamente, até a mochila estar cheia.
*/
void mochila(ITEM items[], int n, int c, int* total, ITEM resultado[]) {
    int restante = c;

    //ordenar vetor
    bubble_sort(items, n);

    for (int i = 0; i < n; i++) {
        if (items[i].peso <= restante) {
            resultado[*total] = items[i];
            (*total)++;

            restante -= items[i].peso;
        }
    }
}

int main(void) {
    int N, C, pi, vi;

    scanf("%d %d", &N, &C);
    ITEM* items = (ITEM*) malloc(N * sizeof(ITEM)); //vetor de importância

    for (int i = 0; i < N; i++) {
        scanf("%d %d", &pi, &vi); 
        items[i] = (ITEM){i, vi, pi};
    }

    ITEM* resultado = (ITEM*) malloc(N * sizeof(ITEM)); // Resultado
    int total = 0;

    //inicar contagem
    clock_t inicio = clock();

    mochila(items, N, C, &total, resultado);

    //fim da execução
    clock_t fim = clock();

    printf("Tempo decorrido: %lf segundos\n", (double)(fim - inicio) / CLOCKS_PER_SEC);

    printf("Mochila:\n");
    for (int i = 0; i < total; i++) {
        printf("Item %d: Valor = %d, Peso = %d\n", resultado[i].id, resultado[i].valor, resultado[i].peso);
    }

    free(items);
    free(resultado);

    return(0);
}