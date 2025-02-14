#include <stdio.h>

#include "GameController.h"

#include "../../model/board/Board.h"
#include "../../model/game/Game.h"
#include "../../view/pages/welcome-page/WelcomePageView.h"
#include "../player/PlayerController.h"

void startTheGame() {
    printf("Game started...\n");
    initGame();
    initWelcomePageView();
}

void clearTheGame() {
    clearGame();
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

bool isGameOver() {
    return game.isOver;
}

char* getWinnerName() {
    return game.players[game.currentPlayerId%2].pseudo;
}

char* getGameName() {
    return game.name;
}

void setGameLevel(const GameLevel level) {
    doSetGameLevel(level);
}

GameLevel getGameLevel() {
    return game.level;
}