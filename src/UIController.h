#ifndef _UICONTROLLER_H
#define _UICONTROLLER_H

#include "scene.h"
#include "character.h"
#include "inventory.h"

void exitGame();
void enterGame();

int showMainMenu(char *gameName);
int showSettings();

void closeSettings();
int showSaveMenu(char **savedFiles);
void closeSaveMenu();

int showInventory(Inventory inventory);
void closeInventory();
int showDialogue(Character character, char *text);
void clearDialogue();


Option promptOptions(char *question, int optionCount, Option *options);
char promptInput(char *question);

int renderScene(Scene scene);
void clearScene();

int showPauseMenu();
void closePauseMenu();

#endif
