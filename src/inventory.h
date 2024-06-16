#pragma once
#ifndef _INVENTORY_H
#define _INVENTORY_H

#include "item.h"

typedef struct {
    Item **items;
    int numItems;
    int maxItems;
} Inventory;

Inventory *createInventory(Item **items, int numItems, int maxItems);

#endif