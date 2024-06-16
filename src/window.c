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
} MainMenuOptions;

typedef struct {
    MainMenuOptions *options;
    int selectedIndex;
} MainMenuState;

const char *options[] = {"Start", "Continue", "Load Save", "Options", "Settings"};
MainMenuOptions mainMenuOptions = {options, 5};
MainMenuState mainMenuState = {&mainMenuOptions, 0};


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
    font = TTF_OpenFont(NOTO_SANS, 24);
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
    SDL_Color white = {255, 255, 255};
    SDL_Surface *surface = TTF_RenderText_Solid(titleFont, gameName, white);
    SDL_Texture *surfaceTexture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect surfaceRect;
    surfaceRect.x = (widthG - surface->w) / 2;
    surfaceRect.y = 160;
    surfaceRect.w = surface->w;
    surfaceRect.h = surface->h;

    SDL_RenderCopy(renderer, surfaceTexture, NULL, &surfaceRect);
    SDL_FreeSurface(surface);

    SDL_SetRenderDrawColor(renderer, 0, 125, 122, 255);
    SDL_RenderPresent(renderer);

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

    background = IMG_LoadTexture(renderer, imagePath);
    SDL_QueryTexture(background, NULL, NULL, &widthG, &heightG);


    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, background, NULL, NULL);
    SDL_RenderPresent(renderer);
    printf("Rendered %s as background\n", imagePath);
    return 0;
}

int renderImage(char *imagePath) {
    if (!fileExists(imagePath)) {
        printf("window.h::renderImage::image %s does not exist!\n", imagePath);
        return -1;
    }
    SDL_Texture *image = IMG_LoadTexture(renderer, imagePath);
    SDL_QueryTexture(image, NULL, NULL, &widthG, &heightG);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, image, NULL, NULL);
    SDL_RenderPresent(renderer);
    return 0;
}

void handleKeyboardInput(SDL_Event *event) {
    switch (event->key.keysym.sym) {
    case SDLK_ESCAPE:
        renderPauseMenu();
        break;
    }
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
            handleKeyboardInput(&event);
            break;
        }
    }
}
