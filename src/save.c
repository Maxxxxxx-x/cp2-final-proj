#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "save.h"
#include "../include/cJSON.h"

void saveGame(Game *game, char *path) {
    cJSON *root = cJSON_CreateObject();
    cJSON_AddStringToObject(root, "player", game->player->name);
    cJSON *inventory = cJSON_CreateArray();
    for (int i = 0; i < game->player->inventory->numItems; i++) {
        cJSON *item = cJSON_CreateObject();
        cJSON_AddStringToObject(item, "name", game->player->inventory->items[i].name);
        cJSON_AddNumberToObject(item, "amount", game->player->inventory->items[i].amount);
        cJSON_AddItemToArray(inventory, item);
    }
    cJSON_AddItemToObject(root, "inventory", inventory);
    cJSON *characters = cJSON_CreateArray();
    for (int i = 0; i < game->numCharacters; i++) {
        cJSON *character = cJSON_CreateObject();
        cJSON_AddStringToObject(character, "id", game->characters[i].id);
        cJSON_AddNumberToObject(character, "happiness", game->characters[i].happiness);
        cJSON_AddNumberToObject(character, "friendship", game->characters[i].friendship);
        cJSON_AddItemToArray(characters, character);
    }
    cJSON_AddItemToObject(root, "characters", characters);
    cJSON_AddNumberToObject(root, "scene", game->currentScene);
    char *json = cJSON_Print(root);
    FILE *file = fopen(path, "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }
    fprintf(file, "%s", json);
    fclose(file);
}

void loadGame(Game *game, char *path){
    FILE *file = fopen(path, "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    rewind(file);

    char *fileContent = (char *)malloc(fileSize + 1);
    if (fileContent == NULL) {
        printf("Error allocating memory!\n");
        fclose(file);
        return;
    }

    size_t bytesRead = fread(fileContent, 1, fileSize, file);
    if (bytesRead != fileSize) {
        printf("Error reading file!\n");
        free(fileContent);
        fclose(file);
        return;
    }

    fileContent[fileSize] = '\0';
    cJSON *root = cJSON_Parse(fileContent);
    if (root == NULL) {
        printf("Error parsing JSON!\n");
        free(fileContent);
        fclose(file);
        return;
    }
    game->player->name = cJSON_GetObjectItem(root, "player")->valuestring;
    cJSON *inventory = cJSON_GetObjectItem(root, "inventory");
    for (int i = 0; i < cJSON_GetArraySize(inventory); i++) {
        cJSON *item = cJSON_GetArrayItem(inventory, i);
        game->player->inventory->items[i].name = cJSON_GetObjectItem(item, "name")->valuestring;
        game->player->inventory->items[i].amount = cJSON_GetObjectItem(item, "amount")->valueint;
    }
    cJSON *characters = cJSON_GetObjectItem(root, "characters");
    for (int i = 0; i < cJSON_GetArraySize(characters); i++) {
        cJSON *character = cJSON_GetArrayItem(characters, i);
        game->characters[i].id = cJSON_GetObjectItem(character, "id")->valuestring;
        game->characters[i].happiness = cJSON_GetObjectItem(character, "happiness")->valueint;
        game->characters[i].friendship = cJSON_GetObjectItem(character, "friendship")->valueint;
    }
    game->currentScene = cJSON_GetObjectItem(root, "scene")->valueint;
    free(fileContent);
    fclose(file);
}