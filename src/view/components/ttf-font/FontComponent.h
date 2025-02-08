#ifndef TTFFONTCOMPONENT_H
#define TTFFONTCOMPONENT_H

#include <SDL_ttf.h>

TTF_Font* createFont(int fontSize);
void destroyFonts();

#endif //TTFFONTCOMPONENT_H