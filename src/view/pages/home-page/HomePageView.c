#include "HomePageView.h"

#include <SDL_events.h>
#include <SDL_render.h>

#include "../../components/renderer/RendererComponent.h"
#include "../../components/morris/app/App.h"
#include "../../components/morris/text-button/TextButton.h"
#include "../../components/morris/textarea/TextArea.h"
#include "../../components/morris/wallpaper/Wallpaper.h"
#include "../play-mode-page/PlayModePageView.h"
#include "../rules-page/RulesPageView.h"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#define MAX_TEXT_BUTTONS 3
#define MAX_WALLPAPERS 1

static TextButton buttons[MAX_TEXT_BUTTONS];
static Wallpaper wallpapers[MAX_WALLPAPERS];
static SDL_Event event;

void renderHomePageUIComponents();
void handelEvents();
void homePageLoop();

void initHomePageView() {
    #ifdef __EMSCRIPTEN__
    emscripten_cancel_main_loop();
    #endif

    wallpapers[0] = (Wallpaper) {"home-page-wp"};

    buttons[0] = (TextButton) {"play-btn", "Play", FLAT_BUTTON,{60, 152-70}, {284, 108}, initPlayModePageView};
    buttons[1] = (TextButton) {"rules-btn", "Rules", FLAT_BUTTON,{60, 412-70}, {284, 108}, initRulesPageView};
    buttons[2] = (TextButton) {"exit-btn", "Exit", FLAT_BUTTON,{60, 672-70}, {284, 108}, app.shutDown};

    #ifdef __EMSCRIPTEN__
        emscripten_set_main_loop(homePageLoop, 0, 1);
    #else
        do {
            homePageLoop();
        } while (app.isRunning());
    #endif

}

void destroyHomePageView() {
    printf("destroyHomePageView...");
}

void homePageLoop() {
    renderHomePageUIComponents();
    handelEvents();
}

void renderHomePageUIComponents() {
    SDL_RenderClear(getRendererInstance());

    for (int i = 0; i < MAX_WALLPAPERS; ++i) renderWallpaper(wallpapers[i]);
    for (int i = 0; i < MAX_TEXT_BUTTONS; ++i) renderTextButton(buttons[i]);

    SDL_RenderPresent(getRendererInstance());
}

void handelEvents() {
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            app.shutDown();
        } else if (event.type == SDL_MOUSEBUTTONDOWN) {
            for (int i = 0; i < MAX_TEXT_BUTTONS; ++i)
                if (isMouseOverTextButton(buttons[i]))
                    buttons[i].onClick();
        }
    }
}