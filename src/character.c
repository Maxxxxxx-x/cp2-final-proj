#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "character.h"
#include "window.h"

// Function to create a new character
Character *createCharacter(char *name, char *avator, char *icon, int happiness, int friendship, char *description) {
    Character *c = malloc(sizeof(Character));
    if (c == NULL) {
        return NULL;
    }
    
    c->happiness = happiness;
    c->friendship = friendship;

    c->name = malloc(strlen(name) + 1);
    if (c->name == NULL) {
        free(c);
        return NULL;
    }
    strcpy(c->name, name);

    c->avator = malloc(strlen(avator) + 1);
    if (c->avator == NULL) {
        free(c->name);
        free(c);
        return NULL;
    }
    strcpy(c->avator, avator);

    c->icon = malloc(strlen(icon) + 1);
    if (c->icon == NULL) {
        free(c->avator);
        free(c->name);
        free(c);
        return NULL;
    }
    strcpy(c->icon, icon);

    c->description = malloc(strlen(description) + 1);
    if (c->description == NULL) {
        free(c->icon);
        free(c->avator);
        free(c->name);
        free(c);
        return NULL;
    }
    strcpy(c->description, description);

    return c;
}

// Function to get the name of a character
char *getName(Character c) {
    return c.name;
}

// Function to get the happiness of a character
int getHappiness(Character c) {
    return c.happiness;
}

// Function to get the friendship of a character
int getFriendship(Character c) {
    return c.friendship;
}

// Function to destroy a character
void destroyCharacter(Character *c) {
    free(c->name);
    free(c);
}

// Function to make a character say something
void say(Character c, char *message) {
    //showDialogue(c, message);
}

// Function to change the happiness of a character
int changeHappiness(Character *c, int amount) {
    c->happiness += amount;
    if (c->happiness < 0) {
        c->happiness = 0;
    }
    return c->happiness;
}

// Function to change the friendship of a character
int changeFriendship(Character *c, int amount) {
    c->friendship += amount;
    if (c->friendship < 0) {
        c->friendship = 0;
    }
    return c->friendship;
}