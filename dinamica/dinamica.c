/*
Uma matriz (tabela) com N linhas e C colunas guarda 
os valores de cada sub problema (uma parte menor)

N -> número de items
C -> peso máximo

Se N = 0 ou C = 0 => Nada será feito

O vetor P armazena os pesos
O vetor V armazena os valores

Usando índices i e j, pode-se definir o item matriz[i][j]
como o sub problema evolvendo P, V i e j.

Existem dois casos para analisar matriz[i][j]:
    Se o peso P[i] > j:
        matriz[i][j] = matriz[i-1][j]
    Senão:
        O valor matriz[i][j] será o valor máximo
        envolvendo matriz[i-1][j] e V[i] + matriz[i-1][j-P[i]]
        
Os números são naturais (isso é muito importante)
Esse algoritmo é um pouco parecido com o algoritmo de otimização de troco

A complexidade do algoritmo não depende só de N, mas de C (capaciade).
Isso ocorre pois a tabela é a principal ação, e a tabela tem formato N * C
*/

#include <stdio.h>
#include <stdlib.h>

int** criar_matriz(int c, int n) {
    int** matriz = (int**) malloc(n * sizeof(int*));
    if (matriz == NULL) {
        exit(1);
    }

    for (int i = 0; i < n; i++) {
        matriz[i] = (int*) malloc(c * sizeof(int));
        if (matriz[i] == NULL) {
            exit(1);
        }
    }

    return(matriz);
}

void apagar_matriz(int*** matriz, int n) {
    for (int i = 0; i < n; i++) {
        free((*matriz)[i]);
        (*matriz)[i] = NULL;
    }

    free(*matriz);
    *matriz = NULL;
}

void matriz_print(int** matriz, int c, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= c; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
}

int* mochila(int p[], int v[], int c, int n) {
    int** matriz = criar_matriz(c, n);

    for (int j = 0; j <= c; j++) {
        matriz[0][j] = 0;

        for (int i = 1; i < n; i++) {
            matriz[i][j] = matriz[i-1][j];

            if (p[i] <= j) {
                int aux1 = matriz[i-1][j];
                int aux2 = (v[i] + matriz[i-1][j - p[i]]);

                if (aux1 > aux2) {
                    matriz[i][j] = aux1;
                } else {
                    matriz[i][j] = aux2;
                }
            }
        }
    }

    matriz_print(matriz, c, n);

    return(NULL);
}

int main(void) {
    int N, C;

    scanf("%d %d", &N, &C);

    int* P = (int*) malloc(N * sizeof(int)); //vetor pesos
    int* V = (int*) malloc(N * sizeof(int)); //vetor valores

    for (int i = 0; i < N; i++) {
        scanf("%d %d", &P[i], &V[i]); //inserir peso e valor de cada item
    }

    mochila(P, V, C, N);

    free(P);
    free(V);

    return(0);
}