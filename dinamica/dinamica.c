/**
 * Código para resolver o problema da mochila usando programação dinâmica
 * 
 * @author Renan Trofino Silva
 * @date 17/09/2024
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
Cria uma matriz de inteiros usando os tamanhos especificados.
A matriz possui ponteiros para ponteiros para int.

As dimensões são passadas por parâmetro (colunas e linhas, respectivamente)

A matriz alocada é retornada.
Em caso de erro, o porgrama é encerrado.
*/
int** criar_matriz(int n, int c) {
    int** matriz = (int**) malloc(n * sizeof(int*));
    if (matriz == NULL) {
        exit(1);
    }

    for (int i = 0; i < n; i++) {
        matriz[i] = (int*) calloc(c, sizeof(int)); //já inicia tudo zerado!
        if (matriz[i] == NULL) {
            exit(1);
        }
    }

    return(matriz);
}

/*
Aloca um vetor dinâmicamente.
O número de items e o tamanho (sizeof) do item são parâmetros.
O vetor é retornado.
*/
void* criar_vetor(int items, int tamanho) {
    void* vetor = (void*) malloc(items * tamanho);
    if (vetor == NULL) {
        exit(1);
    }

    return(vetor);
}

/*
Libera a memória de uma matriz alocada.
Antes de liberar os ponteiros para ponteiros,
libera-se os ponteiros que representam as linhas.
*/
void apagar_matriz(int*** matriz, int n) {
    for (int i = 0; i < n; i++) {
        free((*matriz)[i]);
        (*matriz)[i] = NULL;
    }

    free(*matriz);
    *matriz = NULL;
}

/*
Exibe uma matriz, linha por linha
*/
void matriz_print(int** matriz, int n, int c) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < c; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
}

int max(int v1, int v2) {
    if (v1 > v2) {
        return(v1);
    }

    return(v2);
}

/*
Os números são naturais (isso é muito importante)

Uma matriz (tabela) com N linhas e C colunas guarda 
os valores de cada sub problema (uma parte menor)

N -> número de items
C -> peso máximo

Se N = 0 ou C = 0 => Nada será feito

O vetor P armazena os pesos
O vetor V armazena os valores

Usando índices i e j, pode-se definir o item matriz[i][j]
como o sub problema evolvendo P, V i e j.

O item matriz[i][j] representa os priemiros "i" items
cujo peso somado não ultrapassa "j".

Para matriz[0][j] (nenhum item) => matriz[0][j] = 0

Existem dois casos para analisar matriz[i][j]:
    Se o peso P[i] > j:
        matriz[i][j] = matriz[i-1][j] 
    Senão:
        O valor matriz[i][j] será o valor máximo
        envolvendo matriz[i-1][j] e V[i] + matriz[i-1][j-P[i]]

O primeiro caso ocorre quando o peso do novo item é maior que o limite.
Encontrar a carga máxima, ou seja, maximizar a os valores, é encontrar o item
da matriz que seja matriz[N][C] 

Esse algoritmo é relativamente parecido com o algoritmo de otimização de troco!

A complexidade do algoritmo não depende só de N, mas também de C (capaciade).
Isso ocorre pois a tabela é a principal ação, e a tabela tem formato N * C.

O acesso i-1 é usada pois i = 1 e j = 1 no laço (mas não nos vetores P e V)
*/
void mochila(int p[], int v[], int n, int c, int** resultado, int* total) {
    int** matriz = criar_matriz(n+1, c+1);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= c; j++) {
            if (p[i-1] > j) {
                matriz[i][j] = matriz[i-1][j]; //não cabe
            } else{
                matriz[i][j] = max(matriz[i-1][j], v[i-1] + matriz[i-1][j-p[i-1]]);
            }
        }
    }

    int j = c;
    for (int i = n; i > 0; i--) {
        if (matriz[i][j] == matriz[i-1][j]) {
            //caso oposto ao de cima (não cabe)
            (*resultado)[i-1] = 0;
        } else {
            (*resultado)[i-1] = 1;
            j -= p[i-1];
            //foi usado -> coloque no resultado
        }
    }

    *total = matriz[n][c];

    apagar_matriz(&matriz, n+1);
}

int main(void) {
    int N, C;

    scanf("%d %d", &N, &C);

    int* P = (int*) malloc(N * sizeof(int)); //vetor pesos
    int* V = (int*) malloc(N * sizeof(int)); //vetor valores

    for (int i = 0; i < N; i++) {
        scanf("%d %d", &P[i], &V[i]); //inserir peso e valor de cada item
    }

    int vTotal = 0;
    int pTotal = 0;
    int *res = (int*) criar_vetor(N, sizeof(int));

    //inicar contagem
    clock_t inicio = clock();

    mochila(P, V, N, C, &res, &vTotal);

    //fim da execução
    clock_t fim = clock();

    printf("Tempo decorrido: %lf segundos\n", (double)(fim - inicio) / CLOCKS_PER_SEC);

    printf("Mochila: (");
    for(int i = 0; i < N; i++){
        printf("%d", res[i]);
        if(i != N-1){
            printf(", ");
        }
        
        if (res[i] == 1) {
            pTotal += P[i];
        }
    }
    printf(")\n");

    printf("Valor total: %d\n", vTotal);
    printf("Peso total: %d\n", pTotal);

    free(P);
    free(V);
    free(res);

    return(0);
}