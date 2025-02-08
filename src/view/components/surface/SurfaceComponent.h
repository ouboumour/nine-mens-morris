#ifndef SURFACECOMPONENT_H
#define SURFACECOMPONENT_H

#include <SDL_surface.h>
#include <SDL_ttf.h>

SDL_Surface* createSurface(char* surfaceId, char* surfaceText, TTF_Font* font);
void destroySurfaces();

#endif //SURFACECOMPONENT_H
