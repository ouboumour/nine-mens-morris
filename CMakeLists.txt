cmake_minimum_required(VERSION 3.28)
project(nine-mens-morris C)

# Detect Emscripten build
if(CMAKE_SYSTEM_NAME STREQUAL "Emscripten")
    set(CMAKE_C_COMPILER emcc)
    set(CMAKE_CXX_COMPILER em++)

    set(CMAKE_TOOLCHAIN_FILE "/Users/ouss/CLionProjects/nine-mens-morris/cmake-build-debug/emsdk/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake")

    # Emscripten-specific compiler flags
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s USE_SDL_TTF=2 -s USE_LIBPNG=1")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s USE_SDL_TTF=2 -s USE_LIBPNG=1")

    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='[\"png\"]'")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='[\"png\"]'")


    set(CMAKE_EXECUTABLE_SUFFIX ".html")  # Ensure output is an HTML file
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -o nine-mens-morris.html")


    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --preload-file ${CMAKE_SOURCE_DIR}/src/view/assets@/assets")

#    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s INITIAL_MEMORY=256MB -s ALLOW_MEMORY_GROWTH=1 -s MAX_WEBGL_VERSION=1")

    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s INITIAL_MEMORY=1024MB -s ALLOW_MEMORY_GROWTH=1 -s MAX_WEBGL_VERSION=2 -s USE_WEBGL2=1 -s MIN_WEBGL_VERSION=1 -s OFFSCREEN_FRAMEBUFFER=1")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s MAX_WEBGL_VERSION=2 -s MIN_WEBGL_VERSION=1 -s OFFSCREEN_FRAMEBUFFER=1 -s USE_PTHREADS=0")

    # Include SDL2 headers for Emscripten
    include_directories(
            /Users/ouss/CLionProjects/nine-mens-morris/emsdk/upstream/emscripten/cache/sysroot/include/SDL2
    )

    set(OUTPUT_FILE "nine-mens-morris")  # WebAssembly output

else()

    find_package(SDL2 REQUIRED)
    find_package(SDL2_image REQUIRED)
    find_package(SDL2_ttf REQUIRED)

    include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS})

#    target_link_libraries(${OUTPUT_FILE} SDL2 SDL2_image SDL2_ttf)

    #    set(SDL2_INCLUDE_DIRS /opt/homebrew/include/SDL2)  # Adjust this path if needed
#    set(SDL2_LIBRARIES /opt/homebrew/lib/libSDL2.dylib)  # Adjust this path if needed
#
#    # Manually set paths for SDL2_image
#    set(SDL2_IMAGE_INCLUDE_DIRS /opt/homebrew/include/SDL2)  # Adjust this path if needed
#    set(SDL2_IMAGE_LIBRARIES /opt/homebrew/lib/libSDL2_image.dylib)  # Adjust this path if needed
#
#    # Manually set paths for SDL2_ttf
#    set(SDL2_TTF_INCLUDE_DIRS /opt/homebrew/include/SDL2)  # Adjust this path if needed
#    set(SDL2_TTF_LIBRARIES /opt/homebrew/lib/libSDL2_ttf.dylib)  # Adjust this path if needed

#    include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS})
    set(OUTPUT_FILE "nine-mens-morris")  # Standard executable

endif()

# Add executable
add_executable(${OUTPUT_FILE} src/main.c
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
        src/view/components/utils/commons/Commons.c
        src/view/components/utils/commons/Commons.h
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
        src/view/components/utils/color/Color.c
        src/view/components/utils/color/Color.h
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
        src/model/board-node/BoardNode.c
        src/model/board-node/BoardNode.h
        src/view/components/morris/action-button/SDLActionButton.c
        src/view/components/morris/action-button/ActionButton.h
        src/view/components/morris/popup/popup.c
        src/view/components/morris/popup/popup.h
        src/view/components/animation/AnimationComponent.c
        src/view/components/morris/celebrate-animation/celebrate-animation.c
        src/view/components/morris/celebrate-animation/celebrate-animation.h
        src/view/pages/game-level-page/GameLevelPage.c
        src/view/pages/game-level-page/GameLevelPage.h
        src/view/components/utils/resources/Resources.h)

# Link SDL libraries for native mode
if(NOT CMAKE_SYSTEM_NAME STREQUAL "Emscripten")
    target_link_libraries(${OUTPUT_FILE} ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES})
endif()
