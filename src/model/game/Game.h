#ifndef GAME_H
#define GAME_H

#define MAX_PLAYERS 2

#include "../player/Player.h"

typedef enum {
    PLACEMENT,
    MOVEMENT,
    ATTACK
} GamePhase;

typedef enum {
    NONE,
    EASY,
    MEDIUM
} GameLevel;

typedef struct {
    char* name;
    Player players[MAX_PLAYERS];
    int currentPlayerId;
    GamePhase phase;
    GameLevel level;
    bool isOver;
} Game;

void initGame();
Player* getGamePlayers();

void markGameAsOver();
void clearGame();
void doSetGameLevel(GameLevel level);

extern Game game;

#endif //GAME_H