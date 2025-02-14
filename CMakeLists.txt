cmake_minimum_required(VERSION 3.28)
project(nine-mens-morris C)

set(CMAKE_C_STANDARD 11)

# Manually set paths for SDL2
set(SDL2_INCLUDE_DIRS /opt/homebrew/include/SDL2)  # Adjust this path if needed
set(SDL2_LIBRARIES /opt/homebrew/lib/libSDL2.dylib)  # Adjust this path if needed

# Manually set paths for SDL2_image
set(SDL2_IMAGE_INCLUDE_DIRS /opt/homebrew/include/SDL2)  # Adjust this path if needed
set(SDL2_IMAGE_LIBRARIES /opt/homebrew/lib/libSDL2_image.dylib)  # Adjust this path if needed

# Manually set paths for SDL2_ttf
set(SDL2_TTF_INCLUDE_DIRS /opt/homebrew/include/SDL2)  # Adjust this path if needed
set(SDL2_TTF_LIBRARIES /opt/homebrew/lib/libSDL2_ttf.dylib)  # Adjust this path if needed

# Include directories
include_directories(
        ${SDL2_INCLUDE_DIRS}
        ${SDL2_TTF_INCLUDE_DIRS}
)

add_executable(nine-mens-morris src/main.c
        src/controller/game/GameController.c
        src/controller/game/GameController.h
        src/view/pages/welcome-page/WelcomePageView.c
        src/view/pages/welcome-page/WelcomePageView.h
        src/view/components/sdl/SDLComponent.c
        src/view/components/sdl/SDLComponent.h
        src/view/components/window/WindowComponent.c
        src/view/components/window/WindowComponent.h
        src/view/components/utils/cleaner/Cleaner.c
        src/view/components/utils/cleaner/Cleaner.h
        src/view/components/renderer/RendererComponent.c
        src/view/components/renderer/RendererComponent.h
        src/view/components/sdl-image/SDLImageComponent.c
        src/view/components/sdl-image/SDLImageComponent.h
        src/view/components/sdl-ttf/SDLTTF.c
        src/view/components/sdl-ttf/SDLTTF.h
        src/view/components/ttf-font/FontComponent.c
        src/view/components/ttf-font/FontComponent.h
        src/view/components/texture/TextureComponent.c
        src/view/components/texture/TextureComponent.h
        src/view/components/surface/SurfaceComponent.c
        src/view/components/surface/SurfaceComponent.h
        src/view/pages/home-page/HomePageView.c
        src/view/pages/home-page/HomePageView.h
        src/view/components/morris/text-button/TextButton.h
        src/view/components/morris/text-button/SdlTextButton.c
        src/view/components/morris/commons/Commons.c
        src/view/components/morris/commons/Commons.h
        src/view/components/morris/app/App.c
        src/view/components/morris/app/App.h
        src/view/components/morris/wallpaper/SdlWallpaper.c
        src/view/components/morris/wallpaper/Wallpaper.h
        src/view/components/morris/textarea/SdlTextArea.c
        src/view/components/morris/textarea/TextArea.h
        src/view/pages/rules-page/RulesPageView.c
        src/view/pages/rules-page/RulesPageView.h
        src/view/pages/play-mode-page/PlayModePageView.c
        src/view/pages/play-mode-page/PlayModePageView.h
        src/view/pages/play-page/playPageView.c
        src/view/pages/play-page/playPageView.h
        src/view/components/morris/node/UI_Node.c
        src/view/components/morris/node/UI_Node.h
        src/view/components/morris/reserve-bar/ReserveBar.c
        src/view/components/morris/reserve-bar/ReserveBar.h
        src/view/components/morris/commons/color/Color.c
        src/view/components/morris/commons/color/Color.h
        src/model/player/Player.c
        src/model/player/Player.h
        src/model/game/Game.c
        src/model/game/Game.h
        src/model/board/Board.c
        src/model/board/Board.h
        src/model/node/Node.c
        src/model/node/Node.h
        src/controller/board/BoardController.c
        src/controller/board/BoardController.h
        src/controller/player/PlayerController.c
        src/controller/player/PlayerController.h
        src/view/components/morris/player/UI_Player.c
        src/view/components/morris/player/UI_Player.h
        src/model/boardnode/BoardNode.c
        src/model/boardnode/BoardNode.h
        src/view/components/morris/action-button/SDLActionButton.c
        src/view/components/morris/action-button/ActionButton.h
        src/view/components/morris/popup/popup.c
        src/view/components/morris/popup/popup.h
        src/view/components/animation/AnimationComponent.c
        src/view/components/morris/celebrate-animation/celebrate-animation.c
        src/view/components/morris/celebrate-animation/celebrate-animation.h
        src/view/pages/game-level-page/GameLevelPage.c
        src/view/pages/game-level-page/GameLevelPage.h)

target_link_libraries(nine-mens-morris
            ${SDL2_LIBRARIES}
            ${SDL2_IMAGE_LIBRARIES}
            ${SDL2_TTF_LIBRARIES} )
