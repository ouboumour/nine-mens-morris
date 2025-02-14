#include "BoardController.h"

#include "../../model/board/Board.h"
#include "../../model/boardnode/BoardNode.h"

Node* nodes[MAX_NODES];

void initBoardNodes();

Node** getBoardNodes() {
    BoardNode** boardNodes = findAllBoardNodes();
    for (int i = 0; i < MAX_NODES; ++i) nodes[i] = boardNodes[i]->current;
    return nodes;
}