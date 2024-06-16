#ifndef _WINDOW_H
#define _WINDOW_H

#include <ncurses.h>

#include "character.h"
#include "game.h"

int createWindow(Game game, char *gameName, int height, int width);

int renderMainMenu(char *gameName);
int renderPauseMenu();
int renderSavedMenu();
int renderSettings();
int renderOptions();
int renderInput();

int renderBackground(char *imagePath);
void clearBackground();

int renderCharacter(Character character, CharacterPosition position);
void clearCharacter();

int renderDialogue(Character character, char *text);
void clearDialogue();

void handleEvent(Game game);

#endif
