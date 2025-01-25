#include <stdio.h>

#include "GameController.h"

void initWelcomePageView() {
    printf("initWelcomePageView...\n");
}

void destroyWelcomePageView() {
    printf("destroyWelcomePageView...\n");
}

void startTheGame() {
    printf("Game started...\n");
    initWelcomePageView();
}

void endTheGame() {
    destroyWelcomePageView();
    printf("Bye...\n");
}