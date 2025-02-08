#include "ReserveBar.h"

#include <SDL_render.h>

#include "../../../../controller/player/PlayerController.h"
#include "../../renderer/RendererComponent.h"
#include "../../texture/TextureComponent.h"

void refreshReserveBarAlpha(SDL_Texture* bgTexture, const char* barId);

void renderReserveBar(const ReserveBar bar) {
    char barId[50];
    snprintf(barId, 50, "%s/%d", bar.id, bar.reserve);
    SDL_Texture* bgTexture = createTexture(barId);
    refreshReserveBarAlpha(bgTexture, barId);
    const SDL_Rect bgRect = {bar.coordinates.x, bar.coordinates.y, 49, 666};
    SDL_RenderCopy(getRendererInstance(), bgTexture, NULL, &bgRect);
}

void refreshReserveBarAlpha(SDL_Texture* bgTexture, const char* barId) {
    if (getCurrentPlayer() == getFirstPlayer()) SDL_SetTextureAlphaMod(bgTexture, strstr(barId, "blue") != NULL ? 130 : 255);
    else SDL_SetTextureAlphaMod(bgTexture, strstr(barId, "green") != NULL ? 130 : 255);
}