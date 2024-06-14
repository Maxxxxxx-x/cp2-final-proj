#include <stdio.h>

#include "character.h"
#include "player.h"
#include "window.h"
#include "scene.h"
#include "game.h"

#define HEIGHT 1200
#define WIDTH 1600

Game initGame(char *name, Player *player, Character *characters, int numCharacters, Scene *scenes, int numScenes){
    Game game;
    game.name = name;
    game.player = player;
    game.characters = characters;
    game.numCharacters = numCharacters;
    game.scenes = scenes;
    game.numScenes = numScenes;
    game.currentScene = 0;
    createWindow(game.name, HEIGHT, WIDTH);
    //creaateMainMenu(game.name);
    return game;
}

void startGame(Game *game){

}