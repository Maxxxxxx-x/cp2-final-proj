#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#include "window.h"

#include "game.h"
#include "utils.h"
#include "inventory.h"
#include "character.h"
#include "player.h"
#include "scene.h"
#include "item.h"
#include "../Script/read_yaml.h"

extern Character characters[3];
extern Option options[37];
extern Dialogue dialogues[4];
extern CharacterPosition characterPosition[16];
extern Scene scenes[23];

struct option long_options[] = {
    {"help", no_argument, 0, 'h'},
    {0, 0, 0, 0}
};

void printHelp(){
    printf("Usage: ./engine path/to/your/game\n");
}

int main(int argc, char **argv){
    if (argc < 2){
        printHelp();
        return 1;
    }
    char opt;
    while ((opt = getopt_long(argc, argv, "h", long_options, NULL)) != -1){
        switch (opt){
            case 'h':
                printHelp();
                return 0;
            default:
                printHelp();
                return 1;
        }
    }
    char *path = argv[1];
    if (path[strlen(path) - 1] == '/'){
        path[strlen(path) - 1] = '\0';
    }
    char *script = strcat(path, "/script_chinese.yaml");
    if (!fileExists(script)){
        printf("File %s does not exist!\n", script);
        return 1;
    }
    char *title = "Court Adventures";
    int numCharacters, numScenes;
    Inventory inventory;
    Game game = initGame(title, characters, sizeof(characters), scenes, sizeof(scenes), &inventory);
    //startGame(&game);

    return 0;
}

