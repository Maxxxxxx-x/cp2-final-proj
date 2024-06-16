#pragma once
#include <stdio.h>

#define MAX_CHARACTERS 100
#define MAX_SCENES 100
#define MAX_OPTIONS 10

typedef struct {
    char *id;
    char *name;
    int amount;
    char *image;
    char *description;
} Item;

typedef struct {
    char *id;
    char *name;
    char *description;
    char *avator;
    int happiness;
    int friendship;
    char *icon;    
} Character;

typedef struct {
    char speaker[51];
    char portrait[101];
    char text[201];
} Dialogue;

typedef struct {
    char *description;
    int nextSceneId;
} Option;

typedef enum{
    LEFT,
    RIGHT,
} Position;

typedef struct {
    Character *character;
    Position pos;
} CharacterPosition;

typedef struct {
    int id;
    char *name;
    char *description;
    char *background;
    Item *items;
    int numItems;
    Option *options[2];
    int numOptions;
    Character *speaker;
    char *dialogue;
    CharacterPosition *characters[2];
    int numCharacters;
    
} Scene;


void load_script(const char *filename, Character characters[], int *num_characters, Scene scenes[], int *num_scenes);
void parse_yaml(FILE *file, Character characters[], int *num_characters, Scene scenes[], int *num_scenes);
void print_script(Character characters[], int num_characters, Scene scenes[], int num_scenes);