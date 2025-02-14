#ifndef WINDOWCOMPONENT_H
#define WINDOWCOMPONENT_H

#include <SDL_video.h>

#define WINDOW_WIDTH  1295
#define WINDOW_HEIGHT 780


SDL_Window* getWindowInstance();

void destroyWindow();

#endif //WINDOWCOMPONENT_H