#include "TextArea.h"

#include <SDL_render.h>
#include <SDL_surface.h>

#include "../../renderer/RendererComponent.h"
#include "../../surface/SurfaceComponent.h"
#include "../../texture/TextureComponent.h"
#include "../../ttf-font/FontComponent.h"

void renderTextArea(const TextArea textArea) {
    SDL_Surface* surface = createSurface(textArea.id, textArea.text, createFont(80), textArea.alignement);
    SDL_Texture* texture = createTextureFromSurface(textArea.id, surface);

    const SDL_Rect rect = {textArea.coordinates.x, textArea.coordinates.y, surface->w, surface->h};
    SDL_RenderCopy(getRendererInstance(), texture, NULL, &rect);
}