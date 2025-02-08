#include "App.h"

void shutDownApp();
bool isAppRunning();

bool isUp = true;

App app = {isAppRunning, shutDownApp};

void shutDownApp() {
    isUp = false;
}

bool isAppRunning() {
    return isUp;
}