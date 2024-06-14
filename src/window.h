#ifndef _WINDOW_H
#define _WINDOW_H

#include <ncurses.h>

#include "character.h"

int createWindow(char *gameName, int height, int width);

void showDialogue(Character character, char *text);

int promptPlayer(char *text, int optionsCount, char **options);

#endif
