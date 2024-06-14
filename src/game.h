#pragma once
#ifndef _GAME_H
#define _GAME_H

#include "character.h"
#include "scene.h"
#include "player.h"

typedef struct {
    char *name;
    Player *player;
    Character *characters;
    int numCharacters;
    Scene *scenes;
    int numScenes;
    int currentScene;
} Game;

#endif