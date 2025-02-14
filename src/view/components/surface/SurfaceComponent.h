#ifndef SURFACECOMPONENT_H
#define SURFACECOMPONENT_H

#include <SDL_surface.h>
#include <SDL_ttf.h>

typedef enum {
    ALIGN_LEFT,
    ALIGN_CENTER,
    ALIGN_RIGHT
} Alignement;

SDL_Surface* createSurface(char* surfaceId, char* surfaceText, TTF_Font* font, Alignement alignement);
void destroySurfaces();

#endif //SURFACECOMPONENT_H
