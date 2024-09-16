#ifndef MOCHILA_H
    #define MOCHILA_H
    #include "item.h"
    #include <stdbool.h>

    typedef struct mochila MOCHILA;

    MOCHILA* mochila_criar(ITEM** itens, int W, int tam_max);
    int mochila_atual_peso(MOCHILA* mochila);
    int mochila_peso_max(MOCHILA* mochila);
    ITEM* mochila_itens(MOCHILA* mochila);
    bool mochila_apagar(MOCHILA** mochila);

#endif