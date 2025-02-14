#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "../../model/game/Game.h"

void startTheGame();
void endTheGame();

GamePhase getGamePhase();
char* getWinnerName();
bool isGameOver();
char* getGameName();

void clearTheGame();
GameLevel getGameLevel();

#endif //GAMECONTROLLER_H