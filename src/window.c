#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_ttf.h>

#include "game.h"
#include "save.h"
#include "utils.h"
#include "window.h"

#define NOTO_SANS "./../assets/fonts/NotoSans-Regular.ttf"
#define SAVE_PATH "./../assets/saves"

int widthG;
int heightG;

Game *gameG;

SDL_Event event;
SDL_Window *window;
SDL_Renderer *renderer;

TTF_Font *titleFont;
TTF_Font *font;

SDL_Texture *mainMenu;
SDL_Texture *pauseMenu;
SDL_Texture *savedMenu;
SDL_Texture *settingsMenu;
SDL_Texture *optionsMenu;
SDL_Texture *input;
SDL_Texture *background;
SDL_Texture *character;
SDL_Texture *dialogue;

SDL_Color green = {57, 128, 36};
SDL_Color white = {255, 255, 255};
SDL_Color gray = {200, 200, 200};

bool isMainMenuShown = false;

typedef struct {
    char **items;
    int count;
} Options;

typedef struct {
    Options *option;
    int selectedIndex;
    bool ended;
} OptionsState;

char *options[] = {"Start", "Continue", "Load Save", "Options", "Exit"};
Options mainMenuOptions = {options, 5};
OptionsState mainMenuState = {&mainMenuOptions, 0};

void closeAndExit() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    puts("Window closed");
    return;
}

void handleKeyEvents(OptionsState *state) {
    if (state->ended != false) {
        state->ended = false;
    }

    puts("Handling key inputs...");
    while (SDL_PollEvent(&event) && state->ended != true) {
        if (event.type == SDL_KEYDOWN) {
            printf("%d\n", event.key.keysym.sym);
            switch (event.key.keysym.sym) {
            case SDLK_UP:
                puts("Key Up");
                if (state->selectedIndex < state->option->count) {
                    state->selectedIndex += 1;
                    continue;
                }
                state->selectedIndex = 0;
                break;
            case SDLK_DOWN:
                puts("Key Down");
                if (state->selectedIndex > 0) {
                    state->selectedIndex -= 1;
                    continue;
                }
                state->selectedIndex = state->option->count;
                break;
            case SDLK_RETURN:
                puts("ENTER");
                state->ended = true;
                break;
            default:
                puts("Default");
                break;
            }
        }
    }
    return;
}

int createWindow(Game *game, char *gameName, int width, int height) {
    gameG = game;
    widthG = width;
    heightG = height;
    if (!fileExists(NOTO_SANS)) {
        printf("window.h::Font Not Found::%s does not exists\n", NOTO_SANS);
        return -1;
    }

    if (TTF_Init() < 0) {
        printf("window.h::createWindow::TTF cannot be initialzied. Error: %s\n", TTF_GetError());
        SDL_Quit();
        return -1;
    }

    titleFont = TTF_OpenFont(NOTO_SANS, 48);
    font = TTF_OpenFont(NOTO_SANS, 30);
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("window.h::SDL_Init::%s\n", SDL_GetError());
        return -1;
    }

    window = SDL_CreateWindow(gameName, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width,
                              height, 0);
    if (window == NULL) {
        printf("window.h::SDL_CreateWindow::%s\n", SDL_GetError());
        return -1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if (renderer == NULL) {
        printf("window.h::SDL_CreateREnderer::%s\n", SDL_GetError());
        return -1;
    }

    SDL_RenderPresent(renderer);
    return 0;
}

int renderMainMenu(char *gameName) {
    isMainMenuShown = true;

    SDL_Surface *surface = TTF_RenderText_Solid(titleFont, gameName, white);
    SDL_Texture *surfaceTexture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect surfaceRect;
    surfaceRect.x = (widthG - surface->w) / 2;
    surfaceRect.y = 170;
    surfaceRect.w = surface->w;
    surfaceRect.h = surface->h;

    SDL_RenderCopy(renderer, surfaceTexture, NULL, &surfaceRect);
    SDL_FreeSurface(surface);

    SDL_Rect optionRect;

    for (int i = 0; i < mainMenuOptions.count; i++) {
        optionRect.x = (widthG - TTF_RenderText_Solid(font, mainMenuOptions.items[i], gray)->w) / 2;

        optionRect.y = 500 + (i * 50);
        optionRect.w = TTF_RenderText_Solid(font, mainMenuOptions.items[i], gray)->w;
        optionRect.h = TTF_RenderText_Solid(font, mainMenuOptions.items[i], gray)->h;

        if (i == mainMenuState.selectedIndex) {
            SDL_SetRenderDrawColor(renderer, green.r, green.g, green.b, 255);
        } else {
            SDL_SetRenderDrawColor(renderer, gray.r, gray.g, gray.b, 255);
        }

        SDL_Surface *optionSurface = TTF_RenderText_Solid(
            font, mainMenuOptions.items[i], (i == mainMenuState.selectedIndex) ? green : gray);
        SDL_Texture *optionTexture = SDL_CreateTextureFromSurface(renderer, optionSurface);
        SDL_RenderCopy(renderer, optionTexture, NULL, &optionRect);
        SDL_FreeSurface(optionSurface);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    }

    SDL_RenderPresent(renderer);
    handleKeyEvents(&mainMenuState);

    char *selectedOption = mainMenuOptions.items[mainMenuState.selectedIndex];
    if (strcmp(selectedOption, "Start")) {
        return 0;
    }
    if (strcmp(selectedOption, "Continue")) {
        int fileCount = 0;
        getSaveFiles(SAVE_PATH, &fileCount);
        if (fileCount == 0) {
            puts("No saves found!");
            return -1;
        }
        return 0;
    }
    if (strcmp(selectedOption, "Load Save")) {
        renderSavedMenu();
        return 0;
    }
    if (strcmp(selectedOption, "Options")) {
        renderOptions(scene);
        return 0;
    }

    if (strcmp(selectedOption, "Exit")) {
        closeAndExit();
    }

    return 0;
}

int renderSavedMenu() {
    int fileCount = 0;
    char **saveFileNames = getSaveFiles(SAVE_PATH, &fileCount);

    SDL_Rect rect;
    rect.x = 250;
    rect.y = 250;
    rect.w = 200;
    rect.h = 200;

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &rect);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderPresent(renderer);

    if (fileCount == 0) {
        puts("No save files found!");
        return 0;
    }

    SDL_Rect optionRect;

    Options savedMenuOptions = {saveFileNames, fileCount};
    OptionsState savedMenuState = {&savedMenuOptions, 0};

    for (int i = 0; i < fileCount; i++) {
        optionRect.x =
            (widthG - TTF_RenderText_Solid(font, savedMenuOptions.items[i], gray)->w) / 2;
        optionRect.y = 500 + (i * 50);
        optionRect.w = TTF_RenderText_Solid(font, savedMenuOptions.items[i], gray)->w;
        optionRect.h = TTF_RenderText_Solid(font, savedMenuOptions.items[i], gray)->h;

        if (i == savedMenuState.selectedIndex) {
            SDL_SetRenderDrawColor(renderer, green.r, green.g, green.b, 255);
        } else {
            SDL_SetRenderDrawColor(renderer, gray.r, gray.g, gray.b, 255);
        }

        SDL_Surface *optionSurface = TTF_RenderText_Solid(
            font, savedMenuOptions.items[i], (i == savedMenuState.selectedIndex) ? green : gray);
        SDL_Texture *optionTexture = SDL_CreateTextureFromSurface(renderer, optionSurface);
        SDL_RenderCopy(renderer, optionTexture, NULL, &optionRect);
        SDL_FreeSurface(optionSurface);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    }

    SDL_RenderPresent(renderer);
    handleKeyEvents(&savedMenuState);
    char *fileName = saveFileNames[savedMenuState.selectedIndex];
    loadGame(gameG, fileName);

    return 0;
}

int renderPauseMenu() {
    if (isMainMenuShown) {
        printf("widnow.h::renderPauseMenu::main menu is being shown");
        return -1;
    }

    SDL_Rect rect;
    rect.x = 250;
    rect.y = 250;
    rect.w = 200;
    rect.h = 200;

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &rect);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderPresent(renderer);

    SDL_Rect optionRect;
    char *option[] = {"Resume", "Quick Save", "Load Save", "Exit"};
    Options pauseMenuOptions = {option, 4};
    OptionsState pauseMenuState = {&pauseMenuOptions, 0};

    for (int i = 0; i < pauseMenuOptions.count; i++) {
        optionRect.x =
            (widthG - TTF_RenderText_Solid(font, pauseMenuOptions.items[i], gray)->w) / 2;
        optionRect.y = 500 + (i * 50);
        optionRect.w = TTF_RenderText_Solid(font, pauseMenuOptions.items[i], gray)->w;
        optionRect.h = TTF_RenderText_Solid(font, pauseMenuOptions.items[i], gray)->h;

        if (i == pauseMenuState.selectedIndex) {
            SDL_SetRenderDrawColor(renderer, green.r, green.g, green.b, 255);
        } else {
            SDL_SetRenderDrawColor(renderer, gray.r, gray.g, gray.b, 255);
        }

        SDL_Surface *optionSurface = TTF_RenderText_Solid(
            font, pauseMenuOptions.items[i], (i == pauseMenuState.selectedIndex) ? green : gray);
        SDL_Texture *optionTexture = SDL_CreateTextureFromSurface(renderer, optionSurface);
        SDL_RenderCopy(renderer, optionTexture, NULL, &optionRect);
        SDL_FreeSurface(optionSurface);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    }

    SDL_RenderPresent(renderer);
    handleKeyEvents(&pauseMenuState);
    char *selectedOption = mainMenuOptions.items[mainMenuState.selectedIndex];
    if (strcmp(selectedOption, "Resume")) {
        return 0;
    }
    if (strcmp(selectedOption, "Quick Save")) {
        saveGame(gameG, SAVE_PATH);
        return 0;
    }
    if (strcmp(selectedOption, "Load Save")) {
        renderSavedMenu();
        return 0;
    }

    if (strcmp(selectedOption, "Exit")) {
        closeAndExit();
    }
    return 0;
}

int renderOptions(Scene scene) {

    SDL_Rect rect;
    rect.x = 500;
    rect.y = 250;
    rect.w = 200;
    rect.h = 200;

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &rect);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderPresent(renderer);

    SDL_Rect optionRect;
    Options pauseMenuOptions = {&scene.dialogue, 4};
    OptionsState pauseMenuState = {&pauseMenuOptions, 0};

    for (int i = 0; i < pauseMenuOptions.count; i++) {
        optionRect.x =
            (widthG - TTF_RenderText_Solid(font, pauseMenuOptions.items[i], gray)->w) / 2;
        optionRect.y = 500 + (i * 50);
        optionRect.w = TTF_RenderText_Solid(font, pauseMenuOptions.items[i], gray)->w;
        optionRect.h = TTF_RenderText_Solid(font, pauseMenuOptions.items[i], gray)->h;

        if (i == pauseMenuState.selectedIndex) {
            SDL_SetRenderDrawColor(renderer, green.r, green.g, green.b, 255);
        } else {
            SDL_SetRenderDrawColor(renderer, gray.r, gray.g, gray.b, 255);
        }

        SDL_Surface *optionSurface = TTF_RenderText_Solid(
            font, pauseMenuOptions.items[i], (i == pauseMenuState.selectedIndex) ? green : gray);
        SDL_Texture *optionTexture = SDL_CreateTextureFromSurface(renderer, optionSurface);
        SDL_RenderCopy(renderer, optionTexture, NULL, &optionRect);
        SDL_FreeSurface(optionSurface);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    }

    SDL_RenderPresent(renderer);
    handleKeyEvents(&pauseMenuState);
    return 0;
}

int renderInput() {
    puts("This feature does not work yet");
    return 0;
}

int renderBackground(char *imagePath) {
    if (!fileExists(imagePath)) {
        printf("window.h::renderBackground::image %s does not exists\n", imagePath);
        return -1;
    }

    SDL_Point imageSize;
    background = IMG_LoadTexture(renderer, imagePath);
    SDL_QueryTexture(background, NULL, NULL, &imageSize.x, &imageSize.y);

    printf("Width: %d | Height: %d\n", imageSize.x, imageSize.y);

    float scaleX = (float)(widthG) / (float)(imageSize.x);
    float scaleY = (float)(heightG) / (float)(imageSize.y);
    float scale = (scaleX > scaleY) ? scaleX : scaleY;

    int scaledWidth = (int)(imageSize.x * scale);
    int scaledHeight = (int)(imageSize.y * scale);

    SDL_Rect bgRect;
    bgRect.x = (widthG / imageSize.x) / 2;
    bgRect.y = (heightG / imageSize.y) / 2;
    bgRect.w = scaledWidth;
    bgRect.h = scaledHeight;

    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, background, NULL, &bgRect);
    SDL_RenderPresent(renderer);
    printf("eendered %s as background\n", imagePath);
    SDL_DestroyTexture(background);

    return 0;
}

int renderCharacter(Character character, CharacterPosition position) {
    if (!fileExists(character.avator)) {
        printf("window.h::renderBackground::image %s does not exists\n", character.avator);
        return -1;
    }

    SDL_Point imageSize;
    background = IMG_LoadTexture(renderer, character.avator);
    SDL_QueryTexture(background, NULL, NULL, &imageSize.x, &imageSize.y);

    printf("Width: %d | Height: %d\n", imageSize.x, imageSize.y);

    SDL_Rect bgRect;
    bgRect.x = (position.pos == LEFT) ? 150 : 950;
    bgRect.y = (heightG / imageSize.y) / 2;
    bgRect.w = widthG;
    bgRect.h = heightG;

    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, background, NULL, &bgRect);
    SDL_RenderPresent(renderer);
    printf("eendered %s as background\n", character.avator);
    SDL_DestroyTexture(background);

    return 0;
}

void handleEvent(Game game) {
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            closeAndExit();
            break;
        case SDL_KEYDOWN:
            break;
        }
    }
}
