#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "character.h"

// Function to create a new character
Character *createCharacter(char *name, char *avator, char *icon) {
    Character *c = malloc(sizeof(Character));
    if (c == NULL) {
        return NULL;
    }
    
    c->progress = 0;

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

    return c;
}

// Function to get the name of a character
char *getName(Character c) {
    return c.name;
}

// Function to get the progress of a character
int getProgress(Character c) {
    return c.progress;
}

// Function to destroy a character
void destroyCharacter(Character *c) {
    free(c->name);
    free(c);
}

// Function to make a character say something
void say(Character c, char *message) {
    printf("%s says: %s\n", c.name, message);
}

// Function to make a character progress
void progress(Character *c, int amount) {
    c->progress += amount;
}