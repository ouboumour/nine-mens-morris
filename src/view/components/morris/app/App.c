#include "App.h"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

void shutDownApp();
bool isAppRunning();

bool isUp = true;

App app = {isAppRunning, shutDownApp};

void shutDownApp() {
    isUp = false;
    #ifdef __EMSCRIPTEN__
        emscripten_cancel_main_loop();
        EM_ASM({
            document.getElementById('canvas').style.display = 'none';
            alert("Game has been closed!");
        });
    #endif
}

bool isAppRunning() {
    return isUp;
}