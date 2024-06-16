#pragma once
#ifndef _GAME_H
#define _GAME_H

#include "inventory.h"
#include "character.h"
#include "player.h"
#include "scene.h"

typedef struct {
    char *name;
    Player *player;
    Character *characters;
    int numCharacters;
    Scene *scenes;
    int numScenes;
    int currentScene;
} Game;

Game initGame(char *name, Character *characters, int numCharacters, Scene *scenes, int numScenes, Inventory *playerInventory);
void startGame(Game *game);

#endif