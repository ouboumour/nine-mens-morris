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

#define MAX_TEXT_BUTTONS 3

void initHomePageView() {

    const Wallpaper wallpaper = {"home-page-wp"};
    const TextButton playButton = {"play-btn", "Play", FLAT_BUTTON,{60, 152-70}, {284, 108}, initPlayModePageView};
    const TextButton rulesButton = {"rules-btn", "Rules", FLAT_BUTTON,{60, 412-70}, {284, 108}, initRulesPageView};
    const TextButton exitButton = {"exit-btn", "Exit", FLAT_BUTTON,{60, 672-70}, {284, 108}, app.shutDown};

    const TextButton buttons[MAX_TEXT_BUTTONS] = {playButton, rulesButton, exitButton};

    SDL_Event event;
    do {
        SDL_RenderClear(getRendererInstance());
        renderWallpaper(wallpaper);

        for (int i = 0; i < MAX_TEXT_BUTTONS; ++i) renderTextButton(buttons[i]);

        SDL_RenderPresent(getRendererInstance());

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                app.shutDown();
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                for (int i = 0; i < MAX_TEXT_BUTTONS; ++i) {
                    if (isMouseOverTextButton(buttons[i])) {
                        buttons[i].onClick();
                    }
                }
            }
        }
    } while (app.isRunning());

}

void destroyHomePageView() {
    printf("destroyHomePageView...");
}