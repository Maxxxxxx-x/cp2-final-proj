#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#include "game.h"
#include "utils.h"

struct option long_options[] = {
    {"help", no_argument, 0, 'h'},
    {0, 0, 0, 0}
};

void printHelp(){
    printf("Usage: ./engine scirpt.yml\n");
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
    char *script = argv[1];
    if (!fileExists(script)){
        printf("File %s does not exist!\n", script);
        return 1;
    }
    //parse script
    //init game
    //start game
    return 0;
}