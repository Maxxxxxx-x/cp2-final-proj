#pragma once
#ifndef _SCENE_H
#define _SCENE_H

#include "../Script/read_yaml.h"
#include "item.h"

Scene *createEmptyScene();
Option *createEmptyOption();
Scene *createScene(int id, char *name, char *description, char *background, Item *items, int numItems, Character speaker, char *dialogue, CharacterPosition *characters, int numCharacters, Option *options, int numOptions);
Option *createOption(char *description, int nextSceneId);

#endif