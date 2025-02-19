#include "TextureComponent.h"

#include <SDL_image.h>

#include "../renderer/RendererComponent.h"
#include "../utils/cleaner/Cleaner.h"
#include "../utils/resources/Resources.h"

typedef struct Texture {
    char* name;
    SDL_Texture* sdlTexture;
    struct Texture* next;
} Texture;

SDL_Texture* findTextureByName(char* textureName);
SDL_Texture* createNewTexture(char* textureName);
SDL_Texture* createNewTextureFromSurface(char* textureName, SDL_Surface* surface);
void handleSDLTextureInitFailure(char* textureName);
void handleTextureMemoryAllocationFailure(char* textureName);

Texture* texturesHead = NULL;

SDL_Texture* createTexture(char* textureName) {
    SDL_Texture* texture = findTextureByName(textureName);
    return texture != NULL ? texture : createNewTexture(textureName);
}

SDL_Texture* createTextureFromSurface(char* textureName, SDL_Surface* surface) {
    SDL_Texture* texture = findTextureByName(textureName);
    return texture != NULL ? texture : createNewTextureFromSurface(textureName, surface);
}

void destroytextures() {
    while (texturesHead != NULL) {
        Texture* tempTexture = texturesHead;
        texturesHead = texturesHead->next;
        SDL_DestroyTexture(tempTexture->sdlTexture);
        free(tempTexture);
    }
}

SDL_Texture* findTextureByName(char* textureName) {
    const Texture* currentTexture = texturesHead;
    while (currentTexture != NULL) {
        if (strcmp(currentTexture->name, textureName) == 0) {
            return currentTexture->sdlTexture;
        }
        currentTexture = currentTexture->next;
    }
    return NULL;
}

SDL_Texture* trackAndReturnTexture(char* textureName, SDL_Texture* newSdlTexture) {
    if (newSdlTexture == NULL) {
        handleSDLTextureInitFailure(textureName);
        exit(-1);
    }

    Texture* newTexture = malloc(sizeof(Texture));
    if (newTexture == NULL) {
        handleTextureMemoryAllocationFailure(textureName);
        exit(EXIT_FAILURE);
    }

    newTexture->name = malloc(strlen(textureName) + 1);
    if (newTexture->name == NULL) {
        fprintf(stderr, "Failed to allocate memory for texture name\n");
        exit(EXIT_FAILURE);
    }

    strcpy(newTexture->name, textureName);

    newTexture->sdlTexture = newSdlTexture;
    newTexture->next = texturesHead;

    texturesHead = newTexture;

    return newTexture->sdlTexture;
}

SDL_Texture* createNewTexture(char* textureName) {
    char filePath[70];
    sprintf(filePath, IMAGES_PATH "%s.png", textureName);
    return trackAndReturnTexture(textureName, IMG_LoadTexture(getRendererInstance(), filePath));
}

SDL_Texture* createNewTextureFromSurface(char* textureName, SDL_Surface* surface) {
    return trackAndReturnTexture(textureName, SDL_CreateTextureFromSurface(getRendererInstance(), surface));
}

void handleSDLTextureInitFailure(char* textureName) {
    fprintf(stderr, "Failed to load %s Texture: %s\n", textureName, IMG_GetError());
    destroyAll();
}

void handleTextureMemoryAllocationFailure(char* textureName) {
    fprintf(stderr, "Failed to allocate %zu bytes for %s Texture\n", sizeof(Texture), textureName);
}