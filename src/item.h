#pragma once
#ifndef _ITEM_H
#define _ITEM_H

typedef struct {
    char *name;
    int amount;
    char *image;
    char *description;
} Item;

Item *createItem(char *name, char *description, int amount, char *image);

#endif