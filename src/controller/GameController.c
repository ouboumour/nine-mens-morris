#include <stdio.h>

#include "GameController.h"
#include "../view/WelcomePageView.h"

void startTheGame() {
    printf("Game started...\n");
    initWelcomePageView();
}

void endTheGame() {
    destroyWelcomePageView();
    printf("Bye...\n");
}