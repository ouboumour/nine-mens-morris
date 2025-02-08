#ifndef TEXTURECOMPONENT_H
#define TEXTURECOMPONENT_H

#include <SDL_render.h>

SDL_Texture* createTexture(char* textureName);
SDL_Texture* createTextureFromSurface(char* textureName, SDL_Surface* surface);
void destroytextures();

#endif //TEXTURECOMPONENT_H