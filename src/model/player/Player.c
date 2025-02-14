#include "Player.h"


#include "../board/Board.h"

bool hasUnprotectedPieces(const Player* player) {
    BoardNode** boardNodes = findAllBoardNodes();
    int millsNodesCounter = 0;
    for (int i = 0; i < MAX_NODES; ++i) {
        if (boardNodes[i]->current->occupier != player) continue;
        if (belongsToMill(boardNodes[i]->current)) millsNodesCounter++;
    }
    return player->placedPieces != millsNodesCounter;
}

bool isPlayerStuck(const Player* player) {
    if (player->piecesReserve != 0) return false;

    BoardNode** boardNodes = findAllBoardNodes();
    for (int i = 0; i < MAX_NODES; ++i) {
        if (boardNodes[i]->current->occupier != player) continue;
        if (!isBoardNodeStuck(boardNodes[i])) return false;
    }
    return true;
}

bool didPlayerLoseTooMuchPieces(const Player* player) {
    return player->piecesReserve == 0 && player->placedPieces == 2;
}