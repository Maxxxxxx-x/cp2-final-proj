#pragma once
#ifndef _ITEM_H
#define _ITEM_H

typedef enum {
    ITEM,
    TOOL
} TYPE;

typedef struct {
    char *name;
    int amount;
    TYPE type;
    char *image;
    char *description;
} Item;

#endif