#include "UI_Node.h"

#include <SDL_mouse.h>
#include <SDL_render.h>

#define NODE_WIDTH 33
#define NODE_HEIGHT 33

#include <SDL_timer.h>

#include "../../../../controller/game/GameController.h"
#include "../../../../controller/player/PlayerController.h"
#include "../../renderer/RendererComponent.h"
#include "../../texture/TextureComponent.h"

Uint32 currentTime;
Uint32 lastBlinkTime;

#define BLINK_INTERVAL 500
bool showTexture = true;
bool isBlinkSetedUp = false;

bool isMouseOverNode(UI_Node node);
void occupy(SDL_Texture* bgTexture);
void leave(SDL_Texture* bgTexture);
void mark(SDL_Texture* bgTexture);
void blink(SDL_Texture* bgTexture);


void setupBlink() {
    if (isBlinkSetedUp) return;
    lastBlinkTime = SDL_GetTicks();
    isBlinkSetedUp = true;
}

void renderNode(const UI_Node node) {
    setupBlink();
    char textureId[20];
    sprintf(textureId, "piece/%s/piece", node.node->occupier == getFirstPlayer() ? "green" : (node.node->occupier == getSecondPlayer() ? "blue": (getCurrentPlayer() == getFirstPlayer() ? "green" : "blue")));
    SDL_Texture* bgTexture = createTexture(textureId);

    if (node.node->occupier != NULL) {
        occupy(bgTexture);
    } else {
        if (getGamePhase() == PLACEMENT) {
            if (isMouseOverNode(node)) mark(bgTexture);
            else leave(bgTexture);
        } else if (node.node->isADestCandidate) blink(bgTexture);
        else leave(bgTexture);
    }
    const SDL_Rect bgRect = {node.coordinates.x, node.coordinates.y, NODE_WIDTH, NODE_HEIGHT};
    SDL_RenderCopy(getRendererInstance(), bgTexture, NULL, &bgRect);
}

bool isMouseOverNode(const UI_Node node) {
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    return mouseX >= node.coordinates.x && mouseX <= node.coordinates.x+NODE_WIDTH && mouseY >= node.coordinates.y && mouseY <= node.coordinates.y+NODE_HEIGHT;
}

void mark(SDL_Texture* bgTexture) {
    SDL_SetTextureAlphaMod(bgTexture, 130);
}

void occupy(SDL_Texture* bgTexture) {
    SDL_SetTextureAlphaMod(bgTexture, 255);
}

void leave(SDL_Texture* bgTexture) {
    SDL_SetTextureAlphaMod(bgTexture, 0);
}

void blink(SDL_Texture* bgTexture) {
    currentTime = SDL_GetTicks();
    if (currentTime - lastBlinkTime >= BLINK_INTERVAL) {
        showTexture = !showTexture;
        lastBlinkTime = currentTime;
    }
    SDL_SetTextureAlphaMod(bgTexture, showTexture ? 130 : 0);
}