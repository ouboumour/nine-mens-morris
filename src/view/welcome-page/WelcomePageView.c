#include <SDL_ttf.h>

#include "WelcomePageView.h"

#include "../components/morris/app/App.h"
#include "../components/morris/text-button/TextButton.h"
#include "../components/morris/textarea/TextArea.h"
#include "../components/morris/wallpaper/Wallpaper.h"
#include "../components/renderer/RendererComponent.h"
#include "../components/sdl-image/SDLImageComponent.h"
#include "../components/sdl-ttf/SDLTTF.h"
#include "../components/sdl/SDLComponent.h"
#include "../components/utils/cleaner/Cleaner.h"
#include "../home-page/HomePageView.h"

// TODO: rename the file name to make it clear it's an sdl gui implementation

void initWelcomePageView() {

    initSDL();
    initSDLImage();
    initSDLTTF();

    const Wallpaper wallpaper = {"welcome-page-wp"};
    const TextArea gameNameTextArea = {"game-name-ta", "Nine Men's Morris", {40, 50}};
    const TextButton startButton = {"start-btn", "Start", DIRECTED_BUTTON,{70, 770}, {284, 108}, initHomePageView};

    SDL_Event event;

    do {
        SDL_RenderClear(getRendererInstance());

        renderWallpaper(wallpaper);
        renderTextArea(gameNameTextArea);
        renderTextButton(startButton);

        SDL_RenderPresent(getRendererInstance());

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                app.shutDown();
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                if (isMouseOverTextButton(startButton)) {
                    startButton.onClick();
                }
            }
        }
    } while (app.isRunning());

    destroyAll();
}

void clearWelcomePageView() {
    printf("destroyWelcomePageView...\n");
}

void destroyWelcomePageView() {
    printf("destroyWelcomePageView...\n");
}