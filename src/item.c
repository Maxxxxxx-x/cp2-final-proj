#include <stdlib.h>

#include "item.h"

Item *createEmptyItem() {
    Item *item = (Item *)malloc(sizeof(Item));
    if (item == NULL) {
        return NULL;
    }

    item->name = NULL;
    item->description = NULL;
    item->amount = 1;
    item->image = NULL;

    return item;
}

Item *createItem(char *name, char *description, int amount, char *image) {
    Item *item = (Item *)malloc(sizeof(Item));
    item->name = name;
    item->description = description;
    item->amount = amount;
    item->image = image;
    return item;
}