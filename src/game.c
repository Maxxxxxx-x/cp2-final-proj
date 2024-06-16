#include <stdio.h>
#include <string.h>

#include "window.h"
#include "inventory.h"
#include "character.h"
#include "player.h"
#include "scene.h"
#include "game.h"

#define HEIGHT 1200
#define WIDTH 1600

Game initGame(char *name, Character *characters, int numCharacters, Scene *scenes, int numScenes, Inventory *playerInventory){
    Game game;
    game.name = name;
    game.player = initPlayer("", playerInventory);
    game.characters = characters;
    game.numCharacters = numCharacters;
    game.scenes = scenes;
    game.numScenes = numScenes;
    game.currentScene = 0;

    createWindow(&game, game.name, HEIGHT, WIDTH);
    renderMainMenu(game.name);
    handleEvent(game);

    return game;
}

void startGame(Game *game){
    //enterGame();
    //game->player->name = promptInput("Enter your name: ");
    game->player->name = "Player";
    do{
        //renderScene(game->scenes[game->currentScene]);
        if (strlen(game->scenes[game->currentScene].dialogue) > 0){
            //renderDialogue(game->scenes[game->currentScene].speaker[0], game->scenes[game->currentScene].dialogue);
            printf("%s: %s\n", game->scenes[game->currentScene].speaker[0].name, game->scenes[game->currentScene].dialogue);
        }
        Option option;
        if (game->scenes[game->currentScene].numOptions > 0){
            //renderOptions(game->scenes[game->currentScene].options, game->scenes[game->currentScene].numOptions);
            option = *(game->scenes[game->currentScene].options[0]);
        }
        game->currentScene = option.nextSceneId - 1;
    } while (game->currentScene != 0);
}
