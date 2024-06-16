#include <stdlib.h>

#include "inventory.h"
#include "item.h"

Inventory *createInventory(Item **items, int numItems, int maxItems){
    Inventory *inventory = (Inventory *)malloc(sizeof(Inventory));
    inventory->items = items;
    inventory->numItems = numItems;
    inventory->maxItems = maxItems;
    return inventory;
}