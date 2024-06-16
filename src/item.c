#include <stdlib.h>

#include "item.h"

Item *createItem(char *name, char *description, int amount, char *image) {
    Item *item = (Item *)malloc(sizeof(Item));
    item->name = name;
    item->description = description;
    item->amount = amount;
    item->image = image;
    return item;
}