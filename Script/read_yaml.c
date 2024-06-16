#include <yaml.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_yaml.h"
extern Character characters[3];
extern Option options[37];
extern Dialogue dialogues[4];
extern Actor actor[16];
extern Scene scenes[23];

int main() {
    int num_characters = 3, num_scenes = 23;

    //load_script("script_english.yaml", characters, &num_characters, scenes, &num_scenes);
    print_script(characters, num_characters, scenes, num_scenes);

    return 0;
}

void load_script(const char *filename, Character characters[], int *num_characters, Scene scenes[], int *num_scenes) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    parse_yaml(file, characters, num_characters, scenes, num_scenes);
    fclose(file);
}

void parse_yaml(FILE *file, Character characters[], int *num_characters, Scene scenes[], int *num_scenes) {
    yaml_parser_t parser;
    yaml_event_t event;
    int done = 0;

    yaml_parser_initialize(&parser);
    yaml_parser_set_input_file(&parser, file);

    enum ParseState { NONE, CHARACTERS, CHARACTER, SCENES, SCENE, OPTIONS, OPTION, MOOD };
    enum ParseState state = NONE;
    int current_character = -1;
    int current_scene = -1;
    int current_option = -1;

    while (!done) {
        if (!yaml_parser_parse(&parser, &event)) {
            printf("Parser error %d\n", parser.error);
            exit(EXIT_FAILURE);
        }

        switch (event.type) {
            case YAML_MAPPING_START_EVENT:
                if (state == NONE) {
                    state = CHARACTERS; // Start with characters
                } else if (state == CHARACTERS) {
                    state = CHARACTER;
                    current_character++;
                } else if (state == SCENES) {
                    state = SCENE;
                    current_scene++;
                    scenes[current_scene].optnum = 0; // Initialize option count
                } else if (state == SCENE) {
                    state = OPTIONS;
                    current_option = -1;
                } else if (state == OPTIONS) {
                    state = OPTION;
                    current_option++;
                } else if (state == CHARACTER) {
                    state = MOOD;
                }
                break;
            case YAML_MAPPING_END_EVENT:
                if (state == CHARACTER) {
                    state = CHARACTERS;
                } else if (state == SCENE) {
                    state = SCENES;
                } else if (state == OPTION) {
                    state = OPTIONS;
                } else if (state == OPTIONS) {
                    state = SCENE;
                } else if (state == MOOD) {
                    state = CHARACTER;
                }
                break;
            case YAML_SEQUENCE_START_EVENT:
                if (state == NONE) {
                    state = SCENES;
                } else if (state == SCENE) {
                    state = OPTIONS;
                }
                break;
            case YAML_SEQUENCE_END_EVENT:
                if (state == OPTIONS) {
                    state = SCENE;
                } else if (state == SCENES) {
                    state = NONE;
                }
                break;
            case YAML_SCALAR_EVENT:
                if (state == CHARACTER) {
                    if (strcmp((char *)event.data.scalar.value, "id") == 0) {
                        yaml_event_t value_event;
                        yaml_parser_parse(&parser, &value_event);
                        characters[current_character].id = atoi((char *)value_event.data.scalar.value);
                        yaml_event_delete(&value_event);
                    } else if (strcmp((char *)event.data.scalar.value, "name") == 0) {
                        yaml_event_t value_event;
                        yaml_parser_parse(&parser, &value_event);
                        strncpy(characters[current_character].name, (char *)value_event.data.scalar.value, 50);
                        characters[current_character].name[50] = '\0';
                        yaml_event_delete(&value_event);
                    } else if (strcmp((char *)event.data.scalar.value, "description") == 0) {
                        yaml_event_t value_event;
                        yaml_parser_parse(&parser, &value_event);
                        strncpy(characters[current_character].description, (char *)value_event.data.scalar.value, 200);
                        characters[current_character].description[200] = '\0';
                        yaml_event_delete(&value_event);
                    } else if (strcmp((char *)event.data.scalar.value, "sprite") == 0) {
                        yaml_event_t value_event;
                        yaml_parser_parse(&parser, &value_event);
                        strncpy(characters[current_character].sprite, (char *)value_event.data.scalar.value, 100);
                        characters[current_character].sprite[100] = '\0';
                        yaml_event_delete(&value_event);
                    } else if (strcmp((char *)event.data.scalar.value, "mood") == 0) {
                        state = MOOD;
                    }
                } else if (state == MOOD) {
                    if (strcmp((char *)event.data.scalar.value, "happiness") == 0) {
                        yaml_event_t value_event;
                        yaml_parser_parse(&parser, &value_event);
                        characters[current_character].mood_happiness = atoi((char *)value_event.data.scalar.value);
                        yaml_event_delete(&value_event);
                    } else if (strcmp((char *)event.data.scalar.value, "friendship") == 0) {
                        yaml_event_t value_event;
                        yaml_parser_parse(&parser, &value_event);
                        characters[current_character].mood_friendship = atoi((char *)value_event.data.scalar.value);
                        yaml_event_delete(&value_event);
                    }
                } else if (state == SCENE) {
                    /*if (strcmp((char *)event.data.scalar.value, "id") == 0) {
                        yaml_event_t value_event;
                        yaml_parser_parse(&parser, &value_event);
                        scenes[current_scene].id = atoi((char *)value_event.data.scalar.value);
                        yaml_event_delete(&value_event);
                    } else if (strcmp((char *)event.data.scalar.value, "name") == 0) {
                        yaml_event_t value_event;
                        yaml_parser_parse(&parser, &value_event);
                        strncpy(scenes[current_scene].name, (char *)value_event.data.scalar.value, 50);
                        scenes[current_scene].name[50] = '\0';
                        yaml_event_delete(&value_event);
                    } else if (strcmp((char *)event.data.scalar.value, "description") == 0) {
                        yaml_event_t value_event;
                        yaml_parser_parse(&parser, &value_event);
                        strncpy(scenes[current_scene].description, (char *)value_event.data.scalar.value, 200);
                        scenes[current_scene].description[200] = '\0';
                        yaml_event_delete(&value_event);
                    } else if (strcmp((char *)event.data.scalar.value, "background") == 0) {
                        yaml_event_t value_event;
                        yaml_parser_parse(&parser, &value_event);
                        strncpy(scenes[current_scene].background, (char *)value_event.data.scalar.value, 100);
                        scenes[current_scene].background[100] = '\0';
                        yaml_event_delete(&value_event);
                    }*/
                } else if (state == OPTION) {
                    if (state == CHARACTERS && strcmp((char *)event.data.scalar.value, "scenes") == 0)
                        state = SCENES;
                }
                break;
            default:
                break;
        }

        done = (event.type == YAML_STREAM_END_EVENT);
        yaml_event_delete(&event);
    }

    yaml_parser_delete(&parser);
}


void print_script(Character characters[], int num_characters, Scene scenes[], int num_scenes) {
       
    
    for (int i = 0; i < num_characters; i++) {
        printf("Character %d:\n", characters[i].id);
        printf("  Name: %s\n", characters[i].name);
        printf("  Description: %s\n", characters[i].description);
        printf("  Sprite: %s\n", characters[i].sprite);
        printf("  Mood:\n");
        printf("    Happiness: %d\n", characters[i].mood_happiness);
        printf("    Friendship: %d\n", characters[i].mood_friendship);
    }

    for (int i = 0; i < num_scenes; i++) {
        printf("Scene %d:\n", scenes[i].id);
        printf("  Name: %s\n", scenes[i].name);
        printf("  Description: %s\n", scenes[i].description);
        printf("  Background: %s\n", scenes[i].background);
        if (scenes[i].has_dialogue) {
            printf("  Dialogue:\n");
            printf("    Speaker: %s\n", scenes[i].dialogue->speaker);
            printf("    Portrait: %s\n", scenes[i].dialogue->portrait);
            printf("    Text: %s\n", scenes[i].dialogue->text);
        }
        for (int j = 0; j < scenes[i].optnum; j++) {
            printf("    Option %d:\n", j + 1);
            printf("      Description: %s\n", scenes[i].options[j]->description);
            printf("      Next Scene: %d\n", scenes[i].options[j]->next_scene);
        }
    }
}
