#ifndef PLAYER_H
#define PLAYER_H
#include <stdbool.h>

#define MAX_PSEUDO_LENGTH 20

typedef struct {
    int id;
    char pseudo[MAX_PSEUDO_LENGTH];
    int piecesReserve;
    int placedPieces;
} Player;

bool hasUnprotectedPieces(const Player* player);

bool didPlayerLoseTooMuchPieces(const Player* player);
bool isPlayerStuck(const Player* player);

#endif //PLAYER_H
