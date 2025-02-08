#include <SDL_render.h>

#include "Wallpaper.h"
#include "../../renderer/RendererComponent.h"
#include "../../texture/TextureComponent.h"

void renderWallpaper(const Wallpaper wallpaper) {
    char wallpaperFullId[50];
    sprintf(wallpaperFullId, "wallpapers/%s", wallpaper.id);
    SDL_Texture* backgroundTexture = createTexture(wallpaperFullId);
    SDL_RenderCopy(getRendererInstance(), backgroundTexture, NULL, NULL);
}