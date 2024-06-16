#pragma once
#ifndef _SAVE_H
#define _SAVE_H

#include "game.h"

void saveGame(Game *game, char *path);
void loadGame(Game *game, char *path);
char **getSaveFiles(char *path, int *numFiles);

#endif