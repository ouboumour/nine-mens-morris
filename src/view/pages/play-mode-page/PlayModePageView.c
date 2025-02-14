#include "PlayModePageView.h"

#include <SDL_events.h>
#include <SDL_render.h>

#include "../../components/morris/action-button/ActionButton.h"
#include "../../components/morris/app/App.h"
#include "../../components/morris/text-button/TextButton.h"
#include "../../components/morris/wallpaper/Wallpaper.h"
#include "../../components/renderer/RendererComponent.h"
#include "../game-level-page/GameLevelPage.h"
#include "../home-page/HomePageView.h"
#include "../play-page/playPageView.h"

#define MAX_TEXT_BUTTONS 2

void initPlayModePageView() {
    const Wallpaper wallpaper = {"play-mode-page-wp"};

    const TextButton pvpButton = {"pvp-btn", "P vs P", FLAT_BUTTON,{220, 650}, {284, 108}, initPlayPageView};
    const TextButton pvmButton = {"pvm-btn", "P vs M", FLAT_BUTTON,{790, 650}, {284, 108}, initGameLevelPageView};

    const ActionButton homeButton = {"home-btn", {50, 50}, {77, 80}, initHomePageView};

    const TextButton buttons[MAX_TEXT_BUTTONS] = { pvpButton, pvmButton };

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
                if (isMouseOverActionButton(homeButton)) homeButton.onClick();
                for (int i = 0; i < MAX_TEXT_BUTTONS; ++i) {
                    if (isMouseOverTextButton(buttons[i])) {
                        buttons[i].onClick();
                    }
                }
            }
        }
    } while (app.isRunning());
}


void destroyModePlayPageView();