#ifndef BOARD_H
#define BOARD_H

#include <stdbool.h>

#include "../boardnode/BoardNode.h"

#define MAX_NODES 24

void initBoard();

BoardNode** findAllBoardNodes();

bool belongsToMill(const Node* node);
void doMarkDestinationCandidates(const Node* node);
void clearMarkDestinationCandidates();
bool isBoardNodeStuck(const BoardNode* boardNode);
void clearBoard();

#endif //BOARD_H
