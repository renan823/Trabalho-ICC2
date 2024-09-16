#ifndef ITEM_H
    #define ITEM_H

    typedef struct item_ ITEM;

    ITEM* item_criar(float valor, float peso);
    void item_apagar(ITEM** item);

    float item_get_valor(ITEM* item);
    float item_get_peso(ITEM* item);

#endif