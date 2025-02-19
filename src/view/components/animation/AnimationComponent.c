#include "AnimationComponent.h"

#include "../texture/TextureComponent.h"
#include "../utils/cleaner/Cleaner.h"
#include "../utils/resources/Resources.h"

typedef struct Animation {
    char* id;
    IMG_Animation* sdlAnimation;
    struct Animation* next;
} Animation;

Animation* findAnimationById(char* id);
IMG_Animation* createNewAnimation(char* id);
void handleSDLAnimationInitFailure(char* id);
void handleAnimationMemoryAllocationFailure(char* id);

Animation* animationHead = NULL;

IMG_Animation* createAnimation(char* id) {
    const Animation* animation = findAnimationById(id);
    return animation != NULL ? animation->sdlAnimation : createNewAnimation(id);
}

void destroyAnimations() {
    while (animationHead != NULL) {
        Animation* tmpAnimation = animationHead;
        animationHead = animationHead->next;
        IMG_FreeAnimation(tmpAnimation->sdlAnimation);
        free(tmpAnimation);
    }
}

Animation* findAnimationById(char* id) {
    Animation* currentAnimation = animationHead;
    while (currentAnimation != NULL) {
        if (strcmp(currentAnimation->id, id) == 0) {
            return currentAnimation;
        }
        currentAnimation = currentAnimation->next;
    }
    return NULL;
}

IMG_Animation* createNewAnimation(char* id) {
    char gifPath[100];
    sprintf(gifPath, IMAGES_PATH "%s.gif", id);
    IMG_Animation* newSdlAnimation = IMG_LoadAnimation(gifPath);

    if (newSdlAnimation == NULL) {
        handleSDLAnimationInitFailure(id);
        exit(EXIT_FAILURE);
    }

    Animation* newAnimation = malloc(sizeof(Animation));
    if (newAnimation == NULL) {
        handleAnimationMemoryAllocationFailure(id);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < newSdlAnimation->count; i++) {
        char textureId[50];
        sprintf(textureId, "%s-%d", id, i);
        createTextureFromSurface(textureId, newSdlAnimation->frames[i]);
    }

    newAnimation->id = id;
    newAnimation->sdlAnimation = newSdlAnimation;
    newAnimation->next = animationHead;

    animationHead = newAnimation;

    return newAnimation->sdlAnimation;
}

void handleSDLAnimationInitFailure(char* id) {
    fprintf(stderr, "Failed to load %s animation: %s\n", id, IMG_GetError());
    destroyAll();
}

void handleAnimationMemoryAllocationFailure(char* id) {
    fprintf(stderr, "Failed to allocate %zu bytes for %s Animation\n", sizeof(Animation), id);
}

