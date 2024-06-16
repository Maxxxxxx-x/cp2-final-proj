#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_ttf.h>

#include "game.h"
#include "utils.h"
#include "window.h"

#define NOTO_SANS "./../assets/fonts/NotoSans-Regular.ttf"

int widthG;
int heightG;

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

bool isMainMenuShown = false;

typedef struct {
    const char **items;
    int count;
} Options;

typedef struct {
    Options *option;
    int selectedIndex;
    bool ended;
} OptionsState;

const char *options[] = {"Start", "Continue", "Load Save", "Options", "Settings"};
Options mainMenuOptions = {options, 5};
OptionsState mainMenuState = {&mainMenuOptions, 0};

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

int createWindow(char *gameName, int width, int height) {
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

    SDL_Color green = {57, 128, 36};
    SDL_Color white = {255, 255, 255};
    SDL_Color gray = {200, 200, 200};

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

    return 0;
}

int renderPauseMenu() {
    if (isMainMenuShown) {
        puts("window.h::renderPauseMenu::Already at main menu");
        return -1;
    }
    return 0;
}

int renderSavedMenu() {}
int renderSettings() {}
int renderOptions() {}
int renderInput() {}

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

void handleEvent(Game game) {
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            SDL_Quit();
            puts("Window closed, exiting...");
            exit(EXIT_SUCCESS);
            break;
        case SDL_KEYDOWN:
            break;
        }
    }
}
