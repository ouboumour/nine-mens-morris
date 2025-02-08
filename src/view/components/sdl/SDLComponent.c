#include "SDLComponent.h"

#include <SDL.h>

void handleSDLInitFailure();

void initSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        handleSDLInitFailure();
    }
}

void destroySDL() {
    SDL_Quit();
}

void handleSDLInitFailure() {
    fprintf(stderr, "Failed to initialize SDL: %s\n", SDL_GetError());
    exit(-1);
}