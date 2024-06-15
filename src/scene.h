#pragma once
#ifndef _SCENE_H
#define _SCENE_H

#include "character.h"
#include "item.h"

typedef struct {
    int id;
    char *name;
    char *description;
    char *background;
    Item *items;
    int numItems;
    Character *characters;
    int numCharacters;
    Options *options;
} Scene;

typedef struct {
    char *desciption;
    int nextSceneId;
} Options;

#endif