#ifndef PLAYER_H
#define PLAYER_H
#include <stdbool.h>

typedef struct {
    int id;
    char* pseudo;
    int piecesReserve;
    int placedPieces;
} Player;

bool hasUnprotectedPieces(const Player* player);

#endif //PLAYER_H
