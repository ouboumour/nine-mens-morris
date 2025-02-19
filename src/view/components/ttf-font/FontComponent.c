#include "FontComponent.h"

#include "../utils/cleaner/Cleaner.h"
#include "../utils/resources/Resources.h"

TTF_Font* findFontBySize(int fontSize);
TTF_Font* createNewFont(int fontSize);
void handleTTFFontInitFailure(int fontSize);
void handleFontMemoryAllocationFailure(int fontSize);

typedef struct Font {
    int fontSize;
    TTF_Font* ttfFont;
    struct Font* next;
} Font;

Font* fontsHead = NULL;

TTF_Font* createFont(const int fontSize) {
    TTF_Font* font = findFontBySize(fontSize);
    return font != NULL ? font : createNewFont(fontSize);
}

void destroyFonts() {
    while (fontsHead != NULL) {
        Font* tempFont = fontsHead;
        fontsHead = fontsHead->next;
        TTF_CloseFont(tempFont->ttfFont);
        free(tempFont);
    }
}


TTF_Font* createNewFont(const int fontSize) {
    TTF_Font* newTtfFont = TTF_OpenFont(FONTS_PATH "assassin.ttf", fontSize);
    if (newTtfFont == NULL) {
        handleTTFFontInitFailure(fontSize);
        exit(-1);
    }

    Font* newFont = malloc(sizeof(Font));
    if (newFont == NULL) {
        handleFontMemoryAllocationFailure(fontSize);
        exit(-1);
    }

    newFont->fontSize = fontSize;
    newFont->ttfFont = newTtfFont;
    newFont->next = fontsHead;

    fontsHead = newFont;

    return newFont->ttfFont;
}

TTF_Font* findFontBySize(const int fontSize) {
    const Font* currentFont = fontsHead;
    while (currentFont != NULL) {
        if (currentFont->fontSize == fontSize) {
            return currentFont->ttfFont;
        }
        currentFont = currentFont->next;
    }
    return NULL;
}

void handleTTFFontInitFailure(const int fontSize) {
    fprintf(stderr, "Failed to load font with size %d: %s\n", fontSize, TTF_GetError());
    destroyAll();
}

void handleFontMemoryAllocationFailure(const int fontSize) {
    fprintf(stderr, "Failed to allocate %zu bytes for font with size %d\n", sizeof(Font), fontSize);
}