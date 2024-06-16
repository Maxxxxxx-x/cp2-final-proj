#pragma once
#ifndef _ITEM_H
#define _ITEM_H

typedef struct {
    char *id;
    char *name;
    int amount;
    char *image;
    char *description;
} Item;

Item *createEmptyItem();
Item *createItem(char *name, char *description, int amount, char *image);

#endif