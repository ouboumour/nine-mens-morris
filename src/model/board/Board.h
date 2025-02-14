#ifndef BOARD_H
#define BOARD_H

#include <stdbool.h>

#include "../board-node/BoardNode.h"

#define MAX_NODES 24

void initBoard();

BoardNode** findAllBoardNodes();

bool belongsToMill(const Node* node);
void doMarkDestinationCandidates(const Node* node);
void clearMarkDestinationCandidates();
bool isBoardNodeStuck(const BoardNode* boardNode);
void clearBoard();

int countPotentialMills(const Player* player);
int countMills(const Player* player);

#endif //BOARD_H
