#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#include "window.h"

#include "game.h"
#include "utils.h"

struct option long_options[] = {
    {"help", no_argument, 0, 'h'},
    {0, 0, 0, 0}
};

void printHelp(){
    printf("Usage: ./engine path/to/your/game\n");
}

int main(int argc, char **argv){
    Game game;
    createWindow("Test", 1600, 1200);
    puts("Window created");
    renderBackground("./../assets/images/astolfo.jpeg");
    puts("Background rendered");
    renderMainMenu("Test Main Menu");
    puts("Menu rendered");
    while (1) {
        handleEvent(game);
    }
    return 0;


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

    char *script = strcat(path, "/script.yaml");
    if (!fileExists(script)){
        printf("File %s does not exist!\n", script);
        return 1;
    }
    //parse script
    //init game
    //start game



    return 0;
}
