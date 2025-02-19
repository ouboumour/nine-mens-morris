#include <SDL_ttf.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include "WelcomePageView.h"

#include "../../../controller/game/GameController.h"
#include "../../components/morris/app/App.h"
#include "../../components/morris/text-button/TextButton.h"
#include "../../components/morris/textarea/TextArea.h"
#include "../../components/morris/wallpaper/Wallpaper.h"
#include "../../components/renderer/RendererComponent.h"
#include "../../components/sdl-image/SDLImageComponent.h"
#include "../../components/sdl-ttf/SDLTTF.h"
#include "../../components/sdl/SDLComponent.h"
#include "../../components/utils/cleaner/Cleaner.h"
#include "../home-page/HomePageView.h"

// TODO: rename the file name to make it clear it's an sdl gui implementation

#define MAX_WALLPAPERS 1
#define MAX_TEXT_AREAS 1
#define MAX_TEXT_BUTTONS 1

static Wallpaper wallpapers[MAX_WALLPAPERS];
static TextArea textAreas[MAX_TEXT_AREAS];
static TextButton textButtons[MAX_TEXT_BUTTONS];

static SDL_Event event;

void renderWelcomePageUIComponents();
static void handleEvents();
void welcomePageLoop();

void initWelcomePageView() {
    initSDL();
    initSDLImage();
    initSDLTTF();

    wallpapers[0] = (Wallpaper){"welcome-page-wp"};
    textAreas[0] = (TextArea){"game-name-ta", getGameName(), {10, 55}, ALIGN_CENTER};
    textButtons[0] = (TextButton){"start-btn", "Start", DIRECTED_BUTTON,(Coordinates){32, 630}, (Dimensions){284, 108}, initHomePageView};

    #ifdef __EMSCRIPTEN__
        emscripten_set_main_loop(welcomePageLoop, 0, 1);
    #else
        do {
            welcomePageLoop();
        } while (app.isRunning());
    #endif

    destroyAll();
}

void clearWelcomePageView() {
    printf("destroyWelcomePageView...\n");
}

void destroyWelcomePageView() {
    printf("destroyWelcomePageView...\n");
}

void welcomePageLoop() {
    renderWelcomePageUIComponents();
    handleEvents();
}

void renderWelcomePageUIComponents() {
    SDL_RenderClear(getRendererInstance());

    for (int i = 0; i < MAX_WALLPAPERS; ++i) renderWallpaper(wallpapers[i]);
    for (int i = 0; i < MAX_TEXT_AREAS; ++i) renderTextArea(textAreas[i]);
    for (int i = 0; i < MAX_TEXT_BUTTONS; ++i) renderTextButton(textButtons[i]);

    SDL_RenderPresent(getRendererInstance());
}

void handleEvents() {
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            app.shutDown();
        } else if (event.type == SDL_MOUSEBUTTONDOWN) {
            for (int i = 0; i < MAX_TEXT_BUTTONS; ++i)
                if (isMouseOverTextButton(textButtons[i])) {
                    textButtons[i].onClick();
                }
        }
    }
}