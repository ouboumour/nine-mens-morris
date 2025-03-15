#include "GameLevelPage.h"

#include <SDL_events.h>
#include <SDL_render.h>

#include "../../../controller/game/GameController.h"
#include "../../components/morris/action-button/ActionButton.h"
#include "../../components/renderer/RendererComponent.h"
#include "../../components/morris/app/App.h"
#include "../../components/morris/text-button/TextButton.h"
#include "../../components/morris/wallpaper/Wallpaper.h"
#include "../home-page/HomePageView.h"
#include "../play-page/playPageView.h"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#define MAX_TEXT_BUTTONS 2
#define MAX_ACTION_BUTTONS 1
#define MAX_WALLPAPERS 1

static Wallpaper wallpapers[MAX_WALLPAPERS];
static TextButton textButtons[MAX_TEXT_BUTTONS];
static ActionButton actionButtons[MAX_ACTION_BUTTONS];

static SDL_Event event;

static void renderUIComponents();
static void handleEvents();
void gameLevelLoop();

void playAgainstEasyAI() {
    doSetGameLevel(EASY);
    initPlayPageView();
}

void playMediumEasyAI() {
    doSetGameLevel(MEDIUM);
    initPlayPageView();
}

void initGameLevelPageView() {
    #ifdef __EMSCRIPTEN__
        emscripten_cancel_main_loop();
    #endif

    wallpapers[0] = (Wallpaper) {"game-level-page-wp"};

    actionButtons[0] = (ActionButton) {"home-btn", {50, 50}, {77, 80}, initHomePageView};

    textButtons[0] = (TextButton) {"easy-level-btn", "Easy", FLAT_BUTTON,{970, 80}, {284, 108}, playAgainstEasyAI};
    textButtons[1] = (TextButton) {"mid-level-btn", "Medium", FLAT_BUTTON,{970, 592}, {284, 108}, playMediumEasyAI};

    #ifdef __EMSCRIPTEN__
        emscripten_set_main_loop(gameLevelLoop, 0, 1);
    #else
        do gameLevelLoop(); while (app.isRunning());
    #endif
}

void destroyGameLevelPageView() {
    printf("destroyGameLevelPageView...");
}

void gameLevelLoop() {
    renderUIComponents();
    handleEvents();
}

void renderUIComponents() {
    SDL_RenderClear(getRendererInstance());

    for (int i = 0; i < MAX_WALLPAPERS; ++i) renderWallpaper(wallpapers[i]);
    for (int i = 0; i < MAX_ACTION_BUTTONS; ++i) renderActionButton(actionButtons[i]);
    for (int i = 0; i < MAX_TEXT_BUTTONS; ++i) renderTextButton(textButtons[i]);

    SDL_RenderPresent(getRendererInstance());
}

void handleEvents() {
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            app.shutDown();
        } else if (event.type == SDL_MOUSEBUTTONDOWN) {
            for (int i = 0; i < MAX_TEXT_BUTTONS; ++i)
                if (isMouseOverTextButton(textButtons[i]))
                    textButtons[i].onClick();
            for (int i = 0; i < MAX_ACTION_BUTTONS; ++i)
                if (isMouseOverActionButton(actionButtons[i]))
                    actionButtons[i].onClick();
        }
    }
}