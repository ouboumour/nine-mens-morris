#include "celebrate-animation.h"

#include <SDL_stdinc.h>
#include <SDL_timer.h>
#include <stdbool.h>

#include "../../animation/AnimationComponent.h"
#include "../../renderer/RendererComponent.h"
#include "../../texture/TextureComponent.h"

bool isTicksUp = false;
Uint32 lastTime;

int frame = 0;

void setupTicks() {
    lastTime = SDL_GetTicks();
    isTicksUp = true;
}

void renderCelebration(const CelebrateAnimation animation) {

    if (!isTicksUp) setupTicks();
    const IMG_Animation* sdlAnimation = createAnimation(animation.id);

    const Uint32 currentTime = SDL_GetTicks();
    if (currentTime - lastTime >= sdlAnimation->delays[frame]) {
        frame = (frame + 1) % sdlAnimation->count;
        lastTime = currentTime;
    }

    char textureId[50];
    sprintf(textureId, "%s-%d", animation.id, frame);

    SDL_RenderCopy(getRendererInstance(), createTexture(textureId), NULL, NULL);

}
