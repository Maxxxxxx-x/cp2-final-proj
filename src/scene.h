#pragma once
#ifndef _SCENE_H
#define _SCENE_H

#include "character.h"
#include "item.h"

typedef struct {
    char *name;
    char *description;
    char *background;
    Item *items;
    int numItems;
    Character *characters;
    int numCharacters;
} Scene;

#endif