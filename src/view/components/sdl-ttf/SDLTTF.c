#include "SDLTTF.h"

#include <SDL_ttf.h>

#include "../utils/cleaner/Cleaner.h"

void handleSDLTTFInitFailure();

void initSDLTTF() {
    if (TTF_Init() == -1) {
        handleSDLTTFInitFailure();
    }
}

void destroySDLTTF() {
    TTF_Quit();
}

void handleSDLTTFInitFailure() {
    fprintf(stderr, "Failed to initialize SDL_ttf: %s\n", TTF_GetError());
    destroyAll();
    exit(-1);
}