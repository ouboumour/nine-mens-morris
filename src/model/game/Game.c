#include "Game.h"

#include <stdlib.h>
#include <time.h>

#include "../board/Board.h"

#define MAX_RESERVE 9

Game game;

void registerPlayers();
void chooseFirstToPlayRandomly();
void initPlayersReserve();

void initGame() {
    game.name = "Nine Men's Morris";

    game.players[0].id = 1;
    game.players[1].id = 2;

    registerPlayers();
    initBoard();
    chooseFirstToPlayRandomly();
    initPlayersReserve();
}

void registerPlayers() {
    game.players[0].pseudo = "ouss";
    game.players[1].pseudo = "safaa";
}

void chooseFirstToPlayRandomly() {
    srand(time(NULL));
    game.currentPlayerId = rand() % 2 + 1;
}

void initPlayersReserve() {
    game.players[0].piecesReserve = MAX_RESERVE;
    game.players[1].piecesReserve = MAX_RESERVE;
}

void initPlayersPlacedPieces() {
    game.players[0].placedPieces = 0;
    game.players[1].placedPieces = 0;
}

void initGamePhase() {
    game.phase = PLACEMENT;
}