#pragma once
#ifndef _CHARACTER_H
#define _CHARACTER_H

typedef struct {
    char *id;
    char *name;
    int happiness;
    int friendship;
    char *avator;
    char *icon;
    char *description;
} Character;

char *getName(Character c);
int getHappiness(Character c);
int getFriendship(Character c);
Character *createCharacter(char *name, char *avator, char *icon, int happiness, int friendship, char *description);
void destroyCharacter(Character *c);
void say(Character c, char *message);
int changeHappiness(Character *c, int amount);
int changeFriendship(Character *c, int amount);

#endif