#include <SDL_mouse.h>
#include <SDL_render.h>

#include "ActionButton.h"
#include "../../renderer/RendererComponent.h"
#include "../../texture/TextureComponent.h"

bool isMouseOverActionButton(ActionButton button);

void renderActionButton(const ActionButton button) {
    char buttonFullId[50];
    sprintf(buttonFullId, "buttons/action/%s", button.id);

    SDL_Texture* bgTexture = createTexture(buttonFullId);
    SDL_SetTextureAlphaMod(bgTexture, 130);

    const SDL_Rect bgRect = {button.coordinates.x, button.coordinates.y, button.dimensions.w, button.dimensions.h};

    SDL_SetTextureAlphaMod(bgTexture, isMouseOverActionButton(button) ? 255 : 130);
    SDL_RenderCopy(getRendererInstance(), bgTexture, NULL, &bgRect);
}

bool isMouseOverActionButton(const ActionButton button) {
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    return mouseX >= button.coordinates.x && mouseX <= button.coordinates.x+button.dimensions.w && mouseY >= button.coordinates.y && mouseY <= button.coordinates.y+button.dimensions.h;
}