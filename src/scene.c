#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../Script/read_yaml.h"
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
    
    s->speaker = createEmptyCharacter();
    
    s->dialogue = NULL;
    
    s->characters[0] = NULL;
    s->characters[1] = NULL;
    s->numCharacters = 0;
    
    s->options[0] = NULL;
    s->options[1] = NULL;
    s->numOptions = 0;
    
    return s;
}

Option *createEmptyOption() {
    Option *o = malloc(sizeof(Option));
    if (o == NULL) {
        return NULL;
    }
    
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

    s->speaker = &speaker;

    s->dialogue = malloc(strlen(dialogue) + 1);
    if (s->dialogue == NULL) {
        free(s->background);
        free(s->description);
        free(s->name);
        free(s);
        return NULL;
    }
    strcpy(s->dialogue, dialogue);
    
    s->characters[0] = malloc(sizeof(CharacterPosition) * numCharacters);
    s->characters[0] = characters;
    s->numCharacters = numCharacters;
    
    s->options[0] = malloc(sizeof(Option) * numOptions);
    s->options[0] = options;
    s->numOptions = numOptions;
    
    return s;
}

Option *createOption(char *description, int nextSceneId) {
    Option *o = malloc(sizeof(Option));
    if (o == NULL) {
        return NULL;
    }
    
    o->description = malloc(strlen(description) + 1);
    if (o->description == NULL) {
        free(o);
        return NULL;
    }
    strcpy(o->description, description);
    
    o->nextSceneId = nextSceneId;
    
    return o;
}