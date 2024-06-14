#include <SDL2/SDL.h>

#include "window.h"

int createWindow(char *gameName, int height, int width) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("window.h::SDL_Init::%s\n", SDL_GetError());
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow(gameName, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          height, width, 0);
    if (window == NULL) {
        printf("window.h::SDL_CreateWindow::%s\n", SDL_GetError());
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if (renderer == NULL) {
        printf("window.h::SDL_CreateRenderer::%s\n", SDL_GetError());
        return 1;
    }
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    SDL_Delay(1000000);
}
