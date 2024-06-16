#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "character.h"
#include "scene.h"

Scene *createEmptyScene() {
    Scene *s = malloc(sizeof(Scene));
    if (s == NULL) {
        return NULL;
    }
    
    s->id = -1;
    
    s->name = NULL;
    s->description = NULL;
    s->background = NULL;
    
    s->items = NULL;
    s->numItems = 0;
    
    s->speaker = *createEmptyCharacter();
    
    s->dialogue = NULL;
    
    s->characters = NULL;
    s->numCharacters = 0;
    
    s->options = NULL;
    s->numOptions = 0;
    
    return s;
}

Option *createEmptyOption() {
    Option *o = malloc(sizeof(Option));
    if (o == NULL) {
        return NULL;
    }
    
    o->id = -1;
    
    o->description = NULL;
    
    o->nextSceneId = -1;
    
    return o;
}

Scene *createScene(int id, char *name, char *description, char *background, Item *items, int numItems, Character speaker, char *dialogue, CharacterPosition *characters, int numCharacters, Option *options, int numOptions) {
    Scene *s = malloc(sizeof(Scene));
    if (s == NULL) {
        return NULL;
    }
    
    s->id = id;
    
    s->name = malloc(strlen(name) + 1);
    if (s->name == NULL) {
        free(s);
        return NULL;
    }
    strcpy(s->name, name);
    
    s->description = malloc(strlen(description) + 1);
    if (s->description == NULL) {
        free(s->name);
        free(s);
        return NULL;
    }
    strcpy(s->description, description);
    
    s->background = malloc(strlen(background) + 1);
    if (s->background == NULL) {
        free(s->description);
        free(s->name);
        free(s);
        return NULL;
    }
    strcpy(s->background, background);
    
    s->items = items;
    s->numItems = numItems;

    s->speaker = speaker;

    s->dialogue = malloc(strlen(dialogue) + 1);
    if (s->dialogue == NULL) {
        free(s->background);
        free(s->description);
        free(s->name);
        free(s);
        return NULL;
    }
    strcpy(s->dialogue, dialogue);
    
    s->characters = malloc(sizeof(CharacterPosition) * numCharacters);
    s->characters = characters;
    s->numCharacters = numCharacters;
    
    s->options = malloc(sizeof(Option) * numOptions);
    s->options = options;
    s->numOptions = numOptions;
    
    return s;
}

Option *createOption(int id, char *description, int nextSceneId) {
    Option *o = malloc(sizeof(Option));
    if (o == NULL) {
        return NULL;
    }
    
    o->id = id;
    
    o->description = malloc(strlen(description) + 1);
    if (o->description == NULL) {
        free(o);
        return NULL;
    }
    strcpy(o->description, description);
    
    o->nextSceneId = nextSceneId;
    
    return o;
}