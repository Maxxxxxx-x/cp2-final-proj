#pragma once
#ifndef _PLAYER_H
#define _PLAYER_H

#include "inventory.h"
#include "item.h"

typedef struct {
    char *name;
    Inventory *inventory;
} Player;

Player *initPlayer(char *name, Inventory *inventory);
void getItem(Player *player, Item *item);
void dropItem(Player *player, Item *item);
void useItem(Player *player, Item *item);
void showInventory(Player *player);

#endif