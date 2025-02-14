#include "Game.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../board/Board.h"

#define MAX_RESERVE 9

Game game;

void registerPlayers();
void chooseFirstToPlayRandomly();
void initPlayersReserve();
void initGamePhase();
void initGameOverState();

void clearGame() {
    clearBoard();
    chooseFirstToPlayRandomly();
    initPlayersReserve();
    initGamePhase();
    initGameOverState();
}

void reloadGame() {
    chooseFirstToPlayRandomly();
    initPlayersReserve();
    initGamePhase();
    initGameOverState();
}

void initGame() {
    game.name = "Nine Men's Morris";

    game.players[0].id = 1;
    game.players[1].id = 2;

    registerPlayers();
    initBoard();
    chooseFirstToPlayRandomly();
    initPlayersReserve();
    initGameOverState();
}

void registerPlayers() {
    strcpy(game.players[0].pseudo, "Safaa");
    strcpy(game.players[1].pseudo, "Marwa");

    // printf("Please type the first player pseudo:\n");
    // fgets(game.players[0].pseudo, MAX_PSEUDO_LENGTH, stdin);
    // printf("Please type the second player pseudo:\n");
    // fgets(game.players[1].pseudo, MAX_PSEUDO_LENGTH, stdin);
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

void initGameOverState() {
    game.isOver = false;
}

void markGameAsOver() {
    game.isOver = true;
}