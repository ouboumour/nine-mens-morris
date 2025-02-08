#include "BoardController.h"

#include "../../model/board/Board.h"
#include "../../model/boardnode/BoardNode.h"

Node* nodes[24];

void initBoardNodes();

Node** getBoardNodes() {
    BoardNode** boardNodes = findAllBoardNodes();
    for (int i = 0; i < 24; ++i) {
        nodes[i] = boardNodes[i]->current;
    }
    return nodes;
}