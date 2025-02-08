#include "WindowComponent.h"

#include "../utils/cleaner/Cleaner.h"

#define WINDOW_WIDTH  1588
#define WINDOW_HEIGHT 957

SDL_Window* window = NULL;

SDL_Window* getWindowInstance() {
    if (window != NULL) return window;

    window = SDL_CreateWindow("Nine Men's Morris", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        fprintf(stderr, "Failed to create window: %s\n", SDL_GetError());
        destroyAll();
        exit(-1);
    }
    return window;
}

void destroyWindow() {
    if (window != NULL) {
        SDL_DestroyWindow(window);
    }
}