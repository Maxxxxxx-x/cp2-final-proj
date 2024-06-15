#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "inventory.h"
#include "player.h"
#include "item.h"

Player *initPlayer(char *name, Inventory *inventory) {
    Player *player = (Player *)malloc(sizeof(Player));
    player->name = name;
    player->inventory = inventory;
    player->inventory->items = (Item *)malloc(sizeof(Item) * inventory->maxItems);
    return player;
}

void getItem(Player *player, Item *item) {
    for (int i = 0; i < player->inventory->numItems; i++) {
        if (strcmp(player->inventory->items[i].name, item->name) == 0){
            player->inventory->items[i].amount++;
            return;
        }
    }
    if (player->inventory->numItems < player->inventory->maxItems){
        player->inventory->items[player->inventory->numItems] = *item;
        player->inventory->numItems++;
    }else{
        printf("Inventory is full!\n");
    }
}

void dropItem(Player *player, Item *item) {
    for (int i = 0; i < player->inventory->numItems; i++){
        if (strcmp(player->inventory->items[i].name, item->name) == 0){
            player->inventory->items[i].amount--;
            if (player->inventory->items[i].amount == 0){
                for (int j = i; j < player->inventory->numItems - 1; j++){
                    player->inventory->items[j] = player->inventory->items[j + 1];
                }
                player->inventory->numItems--;
            }
            break;
        }
    }
}

void useItem(Player *player, Item *item) {
    for (int i = 0; i < player->inventory->numItems; i++){
        if (strcmp(player->inventory->items[i].name, item->name) == 0){
            player->inventory->items[i].amount--;
            if (player->inventory->items[i].amount == 0){
                for (int j = i; j < player->inventory->numItems - 1; j++){
                    player->inventory->items[j] = player->inventory->items[j + 1];
                }
                player->inventory->numItems--;
            }
            break;
        }
        // item function
    }
}

void showInventory(Player *player) {
    int i;
    printf("Inventory:\n");
    for (i = 0; i < player->inventory->numItems; i++){
        printf("%s|%d\n", player->inventory->items[i].name, player->inventory->items[i].amount);
    }
}