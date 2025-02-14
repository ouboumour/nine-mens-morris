#include "popup.h"

#include <SDL_render.h>

#include "../../renderer/RendererComponent.h"
#include "../../texture/TextureComponent.h"
#include "../../window/WindowComponent.h"

void renderPopup(const Popup popup) {
    SDL_Texture* bgTexture = createTexture(popup.id);
    SDL_SetTextureAlphaMod(bgTexture, 230);
    const SDL_Rect bgRect = {popup.coordinates.x, popup.coordinates.y, 855, 643};
    SDL_RenderCopy(getRendererInstance(), bgTexture, NULL, &bgRect);
}