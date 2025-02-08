#ifndef GAME_H
#define GAME_H

#define MAX_PLAYERS 2

#include "../player/Player.h"

typedef enum {
    PLACEMENT,
    MOVEMENT,
    ATTACK
} GamePhase;

typedef struct {
    char* name;
    Player players[MAX_PLAYERS];
    int currentPlayerId;
    GamePhase phase;
} Game;

void initGame();
Player* getGamePlayers();

extern Game game;

#endif //GAME_H