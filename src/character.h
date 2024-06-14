#pragma once
#ifndef _CHARACTER_H
#define _CHARACTER_H

typedef struct {
    char *name;
    int progress;
    char *avator;
    char *icon;
} Character;

char *getName(Character c);
int getProgress(Character c);
Character *createCharacter(char *name, char *avator, char *icon);
void destroyCharacter(Character *c);
void say(Character c, char *message);
void progress(Character *c, int amount);

#endif