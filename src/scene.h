#pragma once
#ifndef _SCENE_H
#define _SCENE_H

#include "character.h"
#include "item.h"

typedef struct {
    int id;
    char *description;
    int nextSceneId;
} Option;

typedef enum{
    LEFT,
    RIGHT,
} Position;

typedef struct {
    Character character;
    Position pos;
} CharacterPosition;

typedef struct {
    int id;
    char *name;
    char *description;
    char *background;
    Item *items;
    int numItems;
    Character speaker;
    char *dialogue;
    CharacterPosition *characters;
    int numCharacters;
    Option *options;
    int numOptions;
} Scene;

Scene *createScene(int id, char *name, char *description, char *background, Item *items, int numItems, CharacterPosition *characters, int numCharacters, Option *options, int numOptions);
Option *createOption(int id, char *description, int nextSceneId);

#endif