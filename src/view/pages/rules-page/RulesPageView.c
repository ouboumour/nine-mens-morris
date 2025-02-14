#include "RulesPageView.h"

#include <SDL_events.h>
#include <SDL_render.h>

#include "../../components/morris/action-button/ActionButton.h"
#include "../../components/morris/app/App.h"
#include "../../components/morris/text-button/TextButton.h"
#include "../../components/morris/popup/popup.h"
#include "../../components/morris/wallpaper/Wallpaper.h"
#include "../../components/renderer/RendererComponent.h"
#include "../../components/window/WindowComponent.h"
#include "../home-page/HomePageView.h"

#define MAX_ACTION_BUTTONS 3

int currentPopupPage = 1;
bool doShowNextButton = true;
bool doShowBackButton = false;

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
    const Wallpaper wallpaper = {"rules-page-wp-wip"};

    const ActionButton nextButton = {"next-btn", {923, 580}, {77, 80}, moveToNextChapter};
    const ActionButton backButton = {"back-btn", {300, 580}, {77, 80}, backToPreviousChapter};

    const ActionButton homeButton = {"home-btn", {50, 50}, {77, 80}, initHomePageView};

    const ActionButton actionButtons[MAX_ACTION_BUTTONS] = {backButton, nextButton, homeButton};

    SDL_Event event;

    do {
        const char popupId[10];
        sprintf(popupId, "rules/%d", currentPopupPage);
        const Popup popup = {popupId, {220, 115}};

        SDL_RenderClear(getRendererInstance());
        renderWallpaper(wallpaper);
        renderPopup(popup);

        if (doShowNextButton) renderActionButton(nextButton);
        if (doShowBackButton) renderActionButton(backButton);

        renderActionButton(homeButton);

        SDL_RenderPresent(getRendererInstance());

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                app.shutDown();
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {

                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);
                printf("%d, %d\n", mouseX, mouseY);

                for (int i = 0; i < MAX_ACTION_BUTTONS; ++i) {
                    if (isMouseOverActionButton(actionButtons[i]))
                        actionButtons[i].onClick();
                }
            }
        }
    } while (app.isRunning());
}


void destroyRulesPageView();
