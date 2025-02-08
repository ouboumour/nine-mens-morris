#include <stdio.h>

#include "GameController.h"

#include "../../model/board/Board.h"
#include "../../model/game/Game.h"
#include "../../view/welcome-page/WelcomePageView.h"

void startTheGame() {
    printf("Game started...\n");
    initGame();
    initWelcomePageView();
}

void endTheGame() {
    destroyWelcomePageView();
    printf("Bye...\n");
}

bool isPlacementPhase() {
     return game.players[0].piecesReserve != 0 || game.players[1].piecesReserve != 0;
}

GamePhase getGamePhase() {
    return game.phase;
}