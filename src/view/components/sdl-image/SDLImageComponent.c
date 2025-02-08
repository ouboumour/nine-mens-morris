#include "SDLImageComponent.h"

#include <SDL_image.h>

#include "../utils/cleaner/Cleaner.h"


void handleSDLImageInitFailure();

void initSDLImage() {
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        handleSDLImageInitFailure();
    }
}

void destroySDLImage() {
    IMG_Quit();
}

void handleSDLImageInitFailure() {
    fprintf(stderr, "Failed to initialize SDL_image: %s\n", IMG_GetError());
    destroyAll();
    exit(-1);
}