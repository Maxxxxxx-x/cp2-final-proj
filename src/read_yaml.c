#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "../include/yaml/include/yaml.h"
#include "inventory.h"
#include "character.h"
#include "player.h"
#include "scene.h"
#include "game.h"
#include "item.h"

typedef struct{
    int scene;
    char *model;
    char *prompt;
} Dialogue;

Dialogue *createEmptyDialogue(){
    Dialogue *d = malloc(sizeof(Dialogue));
    if (d == NULL){
        return NULL;
    }

    d->scene = -1;
    d->model = NULL;
    d->prompt = NULL;

    return d;
}

int main() {
    int num_characters, num_scenes, num_items, num_dialogues;
    char *title;
    Character *characters = NULL;
    Scene *scenes = NULL;
    Item *items = NULL;
    Inventory *backpack = NULL;
    Dialogue *open_dialogue = NULL;
    load_script("example_game/script_chinese.yaml", &title, characters, &num_characters, scenes, &num_scenes, items, &num_items, backpack, open_dialogue, &num_dialogues);


    return 0;
}

void load_script(char *filename, char **title, Character *characters, int *num_characters, Scene *scenes, int *num_scenes, Item *items, int *num_items, Inventory *backpack, Dialogue *open_dialogue, int *num_dialogues) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    parse_yaml(file, title, characters, num_characters, scenes, num_scenes, items, num_items, backpack, open_dialogue, num_dialogues);
    fclose(file);
}

void parse_yaml(FILE *file, char **title, Character *characters, int *num_characters, Scene *scenes, int *num_scenes, Item *items, int *num_items, Inventory *backpack, Dialogue *open_dialogue, int *num_dialogues) {
    yaml_parser_t parser;
    //yaml_event_t event;
    yaml_token_t token;
    int done = 0;

    yaml_parser_initialize(&parser);
    yaml_parser_set_input_file(&parser, file);
    characters = NULL;
    *num_characters = 0;
    scenes = NULL;
    *num_scenes = 0;
    items = NULL;
    *num_items = 0;
    backpack = createInventory(NULL, 0, 1);
    open_dialogue = NULL;
    *num_dialogues = 0;
    int status = 0;
    do {
        char **datap;
        char *tk;

        yaml_parser_scan(&parser, &token);
        switch(token.type){
            case YAML_SCALAR_TOKEN:
                tk = (char *)token.data.scalar.value;
    printf("%s|%d\n", tk, status);
                if (strcmp(tk, "title") == 0){
                    status = 1;
                    break;
                }
                if (strcmp(tk, "characters") == 0){
                    status = 2;
                    break;
                }
                if (strcmp(tk, "scenes") == 0){
                    status = 3;
                    break;
                }
                if (strcmp(tk, "items") == 0){
                    status = 4;
                    break;
                }
                if (strcmp(tk, "backpack") == 0){
                    status = 5;
                    break;
                }
                if (strcmp(tk, "open_dialogue") == 0){
                    status = 6;
                    break;
                }
                switch (status){
                    case 1:
                        //title
                        title = strdup(tk);
                        break;
                    case 2:
                        //characters
                        if (strcmp(tk, "id") == 0){
                            characters = realloc(characters, (*num_characters + 1) * sizeof(Character));
                            characters[*num_characters] = *createEmptyCharacter();
                            *num_characters++;
                            status = 11;
                            break;
                        }
                        if (strcmp(tk, "name") == 0){
                            status = 12;
                            break;
                        }
                        if (strcmp(tk, "description") == 0){
                            status = 13;
                            break;
                        }
                        if (strcmp(tk, "sprite") == 0){
                            status = 14;
                            break;
                        }
                        if (strcmp(tk, "mood") == 0){
                            status = 15;
                            break;
                        }
                        break;
                    case 3:
                        //scenes
                        if (strcmp(tk, "id") == 0){
                            scenes = realloc(scenes, (*num_scenes + 1) * sizeof(Scene));
                            scenes[*num_scenes] = *createEmptyScene();
                            *num_scenes++;
                            status = 21;
                            break;
                        }
                        if (strcmp(tk, "name") == 0){
                            status = 22;
                            break;
                        }
                        if (strcmp(tk, "description") == 0){
                            status = 23;
                            break;
                        }
                        if (strcmp(tk, "background") == 0){
                            status = 24;
                            break;
                        }
                        if (strcmp(tk, "options") == 0){
                            status = 25;
                            break;
                        }
                        if (strcmp(tk, "dialogue") == 0){
                            status = 26;
                            break;
                        }
                        break;
                    case 4:
                        //items
                        if (strcmp(tk, "id") == 0){
                            items = realloc(items, (*num_items + 1) * sizeof(Item));
                            items[*num_items] = *createEmptyItem();
                            *num_items++;
                            status = 31;
                            break;
                        }
                        if (strcmp(tk, "name") == 0){
                            status = 32;
                            break;
                        }
                        if (strcmp(tk, "description") == 0){
                            status = 33;
                            break;
                        }
                        if (strcmp(tk, "icon") == 0){
                            status = 34;
                            break;
                        }
                        break;
                    case 5:
                        //backpack
                        if (strcmp(tk, "max_items") == 0){
                            status = 41;
                            break;
                        }
                        if (strcmp(tk, "items") == 0){
                            status = 42;
                            break;
                        }
                        break;
                    case 6:
                        //open_dialogue
                        if (strcmp(tk, "scene") == 0){
                            open_dialogue = realloc(open_dialogue, sizeof(Dialogue) * (*num_dialogues + 1));
                            open_dialogue[*num_dialogues] = *createEmptyDialogue();
                            *num_dialogues++;
                            status = 51;
                            break;
                        }
                        if (strcmp(tk, "dialogue") == 0){
                            status = 52;
                            break;
                        }
                        break;
                    case 11:
                        //characters.id
                        characters[*num_characters - 1].id = atoi(tk);
                        break;
                    case 12:
                        //characters.name
                        characters[*num_characters - 1].name = strdup(tk);
                        break;
                    case 13:
                        //characters.description
                        characters[*num_characters - 1].description = strdup(tk);
                        break;
                    case 14:
                        //characters.sprite
                        characters[*num_characters - 1].icon = strdup(tk);
                        break;
                    case 15:
                        //characters.mood
                        if (strcmp(tk, "happiness") == 0){
                            status = 151;
                            break;
                        }
                        if (strcmp(tk, "friendship") == 0){
                            status = 152;
                            break;
                        }
                        break;
                    case 21:
                        //scenes.id
                        scenes[*num_scenes - 1].id = atoi(tk);
                        break;
                    case 22:
                        //scenes.name
                        scenes[*num_scenes - 1].name = strdup(tk);
                        break;
                    case 23:
                        //scenes.description
                        scenes[*num_scenes - 1].description = strdup(tk);
                        break;
                    case 24:
                        //scenes.background
                        scenes[*num_scenes - 1].background = strdup(tk);
                        break;
                    case 25:
                        //scenes.options
                        if (strcmp(tk, "description") == 0){
                            scenes[*num_scenes - 1].options = realloc(scenes[*num_scenes - 1].options, (scenes[*num_scenes - 1].numOptions + 1) * sizeof(Option));
                            status = 251;
                            break;
                        }
                        if (strcmp(tk, "next_scene") == 0){
                            status = 252;
                            break;
                        }
                        break;
                    case 26:
                        //scenes.dialogue
                        if (strcmp(tk, "speaker") == 0){
                            status = 261;
                            break;
                        }
                        if (strcmp(tk, "portrait") == 0){
                            // status = 262;
                            break;
                        }
                        if (strcmp(tk, "text") == 0){
                            status = 262;
                            break;
                        }
                        break;
                    case 31:
                        //items.id
                        items[*num_items - 1].id = strdup(tk);
                        break;
                    case 32:
                        //items.name
                        items[*num_items - 1].name = strdup(tk);
                        break;
                    case 33:
                        //items.description
                        items[*num_items - 1].description = strdup(tk);
                        break;
                    case 34:
                        //items.icon
                        items[*num_items - 1].image = strdup(tk);
                        break;
                    case 41:
                        //backpack.max_items
                        backpack->maxItems = atoi(tk);
                        break;
                    case 42:
                        for (int i = 0; i < num_items; i++){
                            if (strcmp(tk, items[i].id) == 0){
                                backpack->items[backpack->numItems] = &items[i];
                                backpack->numItems++;
                                break;
                            }
                        }
                        break;
                    case 51:
                        //open_dialogue.scene
                        open_dialogue[*num_dialogues - 1].scene = atoi(tk);
                        break;
                    case 52:
                        //open_dialogue.dialogue
                        if (strcmp(tk, "model") == 0){
                            status = 521;
                            break;
                        }
                        if (strcmp(tk, "prompt") == 0){
                            status = 522;
                            break;
                        }
                        break;
                    case 151:
                        //characters.mood.happiness
                        characters[*num_characters - 1].happiness = atoi(tk);
                        break;
                    case 152:
                        //characters.mood.friendship
                        characters[*num_characters - 1].friendship = atoi(tk);
                        break;
                    case 251:
                        //scenes.options.description
                        scenes[*num_scenes].options[scenes[*num_scenes].numOptions].description = strdup(tk);
                        break;
                    case 252:
                        //scenes.options.next_scene
                        scenes[*num_scenes].options[scenes[*num_scenes].numOptions].nextSceneId = atoi(tk);
                        scenes[*num_scenes - 1].numOptions++;
                        break;
                    case 261:
                        //scenes.dialogue.speaker
                        for (int i = 0; i < num_characters; i++){
                            if (strcmp(tk, characters[i].name) == 0){
                                scenes[*num_scenes - 1].speaker = characters[i];
                                break;
                            }
                        }
                        break;
                    case 262:
                        //scenes.dialogue.text
                        scenes[*num_scenes - 1].dialogue = strdup(tk);
                        break;
                    case 521:
                        //open_dialogue.dialogue.model
                        open_dialogue[*num_dialogues - 1].model = strdup(tk);
                        break;
                    case 522:
                        //open_dialogue.dialogue.prompt
                        open_dialogue[*num_dialogues - 1].prompt = strdup(tk);
                        break;
                }
                break;
        }
    } while(token.type != YAML_STREAM_END_TOKEN);

    yaml_token_delete(&token);
    yaml_parser_delete(&parser);
    return;
}
