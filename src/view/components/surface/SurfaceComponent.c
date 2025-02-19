#include "SurfaceComponent.h"

#include <SDL_ttf.h>

#include  "../utils/color/Color.h"

#include "../utils/cleaner/Cleaner.h"

typedef struct Surface {
    char* id;
    char* text;
    SDL_Surface* sdlSurface;
    struct Surface* next;
} Surface;

Surface* surfacesHead = NULL;

SDL_Surface* createNewSurface(char* surfaceId, char* surfaceText, TTF_Font* font, Alignement alignement);
void handleSDLSurfaceInitFailure(const char* surfaceText);
void handleSurfaceMemoryAllocationFailure(const char* surfaceText);
SDL_Surface* findSdlSurfaceById(const char* surfaceId);

SDL_Surface* createSurface(char* surfaceId, char* surfaceText, TTF_Font* font, Alignement alignement) {
    SDL_Surface* sdlSurface = findSdlSurfaceById(surfaceId);
    return sdlSurface != NULL ? sdlSurface : createNewSurface(surfaceId, surfaceText, font, alignement);
}

int toSdlAlignment(const Alignement alignement) {
    switch (alignement) {
        case ALIGN_CENTER: return TTF_WRAPPED_ALIGN_CENTER;
        case ALIGN_RIGHT: return TTF_WRAPPED_ALIGN_RIGHT;
        default: return TTF_WRAPPED_ALIGN_LEFT;
    }
}

SDL_Surface* createNewSurface(char* surfaceId, char* surfaceText, TTF_Font* font, const Alignement alignement) {

    TTF_SetFontWrappedAlign(font, toSdlAlignment(alignement));

    const RgbaColor textColor = toRgba(pickColorFromComponentId(surfaceId));
    SDL_Surface* newSdlSurface = TTF_RenderText_Blended_Wrapped(font , surfaceText,(SDL_Color) {textColor.r, textColor.g, textColor.b, textColor.a}, 400);
    if (newSdlSurface == NULL) {
        handleSDLSurfaceInitFailure(surfaceText);
        exit(-1);
    }

    Surface* newSurface = malloc(sizeof(Surface));
    if (newSurface == NULL) {
        handleSurfaceMemoryAllocationFailure(surfaceText);
        exit(-1);
    }

    newSurface->id = surfaceId;
    newSurface->text = surfaceText;
    newSurface->sdlSurface = newSdlSurface;
    newSurface->next = surfacesHead;

    surfacesHead = newSurface;
    return newSurface->sdlSurface;
}

void destroySurfaces() {
    while (surfacesHead != NULL) {
        Surface* tempSurface = surfacesHead;
        surfacesHead = surfacesHead->next;
        SDL_FreeSurface(tempSurface->sdlSurface);
        free(tempSurface);
    }
}


SDL_Surface* findSdlSurfaceById(const char* surfaceId) {
    const Surface* currentSurface = surfacesHead;
    while (currentSurface != NULL) {
        if (strcmp(currentSurface->text, surfaceId) == 0) {
            return currentSurface->sdlSurface;
        }
        currentSurface = currentSurface->next;
    }
    return NULL;
}


void handleSDLSurfaceInitFailure(const char* surfaceText) {
    fprintf(stderr, "Failed to render %s surface: %s\n", surfaceText, TTF_GetError());
    destroyAll();
}

void handleSurfaceMemoryAllocationFailure(const char* surfaceText) {
    fprintf(stderr, "Failed to allocate %zu bytes for %s Surface\n", sizeof(Surface), surfaceText);
}