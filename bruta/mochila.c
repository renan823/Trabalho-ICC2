#include "mochila.h"
#include <stdlib.h>
#include <stdbool.h>

struct mochila{
    ITEM** itens;
    float peso_max;
    int tam_max;
};

MOCHILA* mochila_criar(ITEM** itens, int W, int tam_max){
    MOCHILA* mochila = (MOCHILA*) malloc(sizeof(MOCHILA));

    if(mochila != NULL){
        mochila->itens = itens;
        mochila->peso_max = W;
        mochila->tam_max = tam_max;
    }

    return mochila;    
}

int mochila_atual_peso(MOCHILA* mochila){
    float peso = 0;
    for(int i = 0; i < mochila->tam_max; i++){
        peso += item_get_peso(mochila->itens[i]);
    }

    return peso;
}

int mochila_peso_max(MOCHILA* mochila){
    return mochila->peso_max;
}

ITEM* mochila_itens(MOCHILA* mochila){
    return *(mochila->itens);
}

bool mochila_apagar(MOCHILA** mochila){
    if(mochila != NULL){
        free(*mochila);
        *mochila = NULL;

        return true;
    }

    return false;    
}