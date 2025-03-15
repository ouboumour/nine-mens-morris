#include "RulesPageView.h"

#include <SDL_events.h>
#include <SDL_render.h>

#include "../../components/morris/action-button/ActionButton.h"
#include "../../components/morris/app/App.h"
#include "../../components/morris/text-button/TextButton.h"
#include "../../components/morris/popup/popup.h"
#include "../../components/morris/wallpaper/Wallpaper.h"
#include "../../components/renderer/RendererComponent.h"
#include "../home-page/HomePageView.h"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#define MAX_ACTION_BUTTONS 3
#define MAX_WALLPAPERS 1

static ActionButton actionButtons[MAX_ACTION_BUTTONS];
static Wallpaper wallpapers[MAX_ACTION_BUTTONS];

int currentPopupPage = 1;
bool doShowNextButton = true;
bool doShowBackButton = false;

static SDL_Event event;

static void renderUIComponents();
static void handleEvents();
void rulesPageLoop();

void refreshBackButton() {
    doShowBackButton = currentPopupPage != 1;
}

void refresMextButton() {
    doShowNextButton = currentPopupPage != 4;
}

void moveToNextChapter() {
    if (currentPopupPage != 4) currentPopupPage++;
    refreshBackButton();
    refresMextButton();
}

void backToPreviousChapter() {
    if (currentPopupPage != 1) currentPopupPage--;
    refreshBackButton();
    refresMextButton();
}

void initRulesPageView() {
    #ifdef __EMSCRIPTEN__
        emscripten_cancel_main_loop();
    #endif

    wallpapers[0] = (Wallpaper) {"rules-page-wp-wip"};

    actionButtons[0] = (ActionButton) {"home-btn", {50, 50}, {77, 80}, initHomePageView};
    actionButtons[1] = (ActionButton) {"next-btn", {923, 580}, {77, 80}, moveToNextChapter};
    actionButtons[2] = (ActionButton) {"back-btn", {300, 580}, {77, 80}, backToPreviousChapter};

    #ifdef __EMSCRIPTEN__
        emscripten_set_main_loop(rulesPageLoop, 0, 1);
    #else
        do rulesPageLoop(); while (app.isRunning());
    #endif
}


void destroyRulesPageView();

static void renderUIComponents() {
    char popupId[10];
    sprintf(popupId, "rules/%d", currentPopupPage);
    const Popup popup = {popupId, {220, 115}};

    SDL_RenderClear(getRendererInstance());
    renderWallpaper(wallpapers[0]);
    renderPopup(popup);

    renderActionButton(actionButtons[0]);
    if (doShowNextButton) renderActionButton(actionButtons[1]);
    if (doShowBackButton) renderActionButton(actionButtons[2]);

    SDL_RenderPresent(getRendererInstance());
}

static void handleEvents() {
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            app.shutDown();
        } else if (event.type == SDL_MOUSEBUTTONDOWN) {
            for (int i = 0; i < MAX_ACTION_BUTTONS; ++i) {
                if (isMouseOverActionButton(actionButtons[i]))
                    actionButtons[i].onClick();
            }
        }
    }
}

void rulesPageLoop() {
    renderUIComponents();
    handleEvents();
}