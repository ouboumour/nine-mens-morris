#include "RendererComponent.h"

#include "../utils/cleaner/Cleaner.h"
#include "../window/WindowComponent.h"

SDL_Renderer* renderer = NULL;

SDL_Renderer* getRendererInstance() {
    if (renderer != NULL) return renderer;
    renderer = SDL_CreateRenderer(getWindowInstance(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) {
        fprintf(stderr, "Failed to create renderer: %s\n", SDL_GetError());
        destroyAll();
        exit(-1);
    }
    return renderer;
}

void destroyRenderer() {
    if (renderer != NULL) {
        SDL_DestroyRenderer(renderer);
    }
}