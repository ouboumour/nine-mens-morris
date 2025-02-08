#include "Player.h"

#include "../board/Board.h"

bool hasUnprotectedPieces(const Player* player) {
    BoardNode** boardNodes = findAllBoardNodes();
    int millsNodesCounter = 0;
    for (int i = 0; i < 24; ++i) {
        if (boardNodes[i]->current->occupier != player) continue;
        if (belongsToMill(boardNodes[i]->current)) millsNodesCounter++;
    }
    return player->placedPieces != millsNodesCounter;
}
