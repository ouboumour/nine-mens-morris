#include "Cleaner.h"

#include "../../animation/AnimationComponent.h"
#include "../../renderer/RendererComponent.h"
#include "../../sdl-image/SDLImageComponent.h"
#include "../../sdl-ttf/SDLTTF.h"
#include "../../sdl/SDLComponent.h"
#include "../../surface/SurfaceComponent.h"
#include "../../texture/TextureComponent.h"
#include "../../ttf-font/FontComponent.h"
#include "../../window/WindowComponent.h"

void destroyAll() {
    destroyAnimations();
    destroySurfaces();
    destroytextures();
    destroyFonts();
    destroyRenderer();
    destroyWindow();
    destroySDLTTF();
    destroySDLImage();
    destroySDL();
}
