#ifndef BOARD_H
#define BOARD_H

#include <stdbool.h>

#include "../boardnode/BoardNode.h"

void initBoard();

BoardNode** findAllBoardNodes();

bool belongsToMill(const Node* node);
void doMarkDestinationCandidates(const Node* node);
void clearMarkDestinationCandidates();

#endif //BOARD_H
