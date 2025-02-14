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

#define MAX_TEXT_BUTTONS 2

void playAgainstEasyAI() {
    doSetGameLevel(EASY);
    initPlayPageView();
}

void playMediumEasyAI() {
    doSetGameLevel(MEDIUM);
    initPlayPageView();
}

void initGameLevelPageView() {

    const Wallpaper wallpaper = {"game-level-page-wp"};
    const ActionButton homeButton = {"home-btn", {50, 50}, {77, 80}, initHomePageView};
    const TextButton easyLevelButton = {"easy-level-btn", "Easy", FLAT_BUTTON,{970, 80}, {284, 108}, playAgainstEasyAI};
    const TextButton middLevelButton = {"mid-level-btn", "Medium", FLAT_BUTTON,{970, 592}, {284, 108}, playMediumEasyAI};

    const TextButton buttons[MAX_TEXT_BUTTONS] = {easyLevelButton, middLevelButton};

    SDL_Event event;
    do {
        SDL_RenderClear(getRendererInstance());
        renderWallpaper(wallpaper);
        renderActionButton(homeButton);

        for (int i = 0; i < MAX_TEXT_BUTTONS; ++i) renderTextButton(buttons[i]);

        SDL_RenderPresent(getRendererInstance());

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                app.shutDown();
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                for (int i = 0; i < MAX_TEXT_BUTTONS; ++i) {
                    if (isMouseOverTextButton(buttons[i])) {
                        buttons[i].onClick();
                    } else if (isMouseOverActionButton(homeButton)) {
                        homeButton.onClick();
                    }
                }
            }
        }
    } while (app.isRunning());

}

void destroyGameLevelPageView() {
    printf("destroyGameLevelPageView...");
}