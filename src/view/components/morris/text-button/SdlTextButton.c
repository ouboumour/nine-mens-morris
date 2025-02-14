#include "TextButton.h"

#include <SDL_render.h>

#include "../../renderer/RendererComponent.h"
#include "../../surface/SurfaceComponent.h"
#include "../../texture/TextureComponent.h"
#include "../../ttf-font/FontComponent.h"

void handleSdlButtonMemoryAllocationFailure(const char* id);
bool isMouseOverTextButton(TextButton button);

void renderTextButton(const TextButton button) {
    char buttonFullId[50];
    sprintf(buttonFullId, "buttons/text/%s", button.type == DIRECTED_BUTTON ? "directed-btn" : "flat-btn");

    SDL_Texture* bgTexture = createTexture(buttonFullId);
    SDL_SetTextureAlphaMod(bgTexture, 130);

    SDL_Surface* labelSurface = createSurface(button.id, button.label, createFont(45), ALIGN_CENTER);
    SDL_Texture* labelTexture = createTextureFromSurface(button.label, labelSurface);

    const SDL_Rect bgRect = {button.coordinates.x, button.coordinates.y, button.dimensions.w, button.dimensions.h};

    const SDL_Rect labelRect = {
        button.coordinates.x - (button.type == DIRECTED_BUTTON ? 10 : 0) + (button.dimensions.w-labelSurface->w)/2,
        button.coordinates.y - (button.type == DIRECTED_BUTTON ? 3 : 0) + (button.dimensions.h-labelSurface->h)/2,
        labelSurface->w,
        labelSurface->h
    };

    SDL_SetTextureAlphaMod(bgTexture, isMouseOverTextButton(button) ? 255 : 130);

    SDL_RenderCopy(getRendererInstance(), bgTexture, NULL, &bgRect);
    SDL_RenderCopy(getRendererInstance(), labelTexture, NULL, &labelRect);

}

bool isMouseOverTextButton(const TextButton button) {
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    return mouseX >= button.coordinates.x && mouseX <= button.coordinates.x+button.dimensions.w && mouseY >= button.coordinates.y && mouseY <= button.coordinates.y+button.dimensions.h;
}