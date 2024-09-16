#include "item.h"

#include <stdlib.h>

struct item_ {
    int valor;
    int peso;
};

ITEM* item_criar(int valor, int peso) {
    ITEM* item = (ITEM*) malloc(sizeof(ITEM));

    if (item != NULL) {
        item->valor = valor;
        item->peso = peso;
    }

    return(item);
}

void item_apagar(ITEM** item) {
    if (*item == NULL) {
        return;
    }

    free(*item);
    *item = NULL;
}

float item_get_peso(ITEM* item) {
    if (item == NULL) {
        return(-1);
    }

    return(item->peso);
}

float item_get_valor(ITEM* item) {
    if (item == NULL) {
        return(-1);
    }

    return(item->valor);
}