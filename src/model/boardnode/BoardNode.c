#include "BoardNode.h"

#include <stdio.h>
#include <stdlib.h>

void handleBoardNodeMemoryAllocationFailure(int boardNodeId);


BoardNode* createBoardNode(Node* node) {
    BoardNode* boardNode = malloc(sizeof(BoardNode));

    if (boardNode == NULL) {
        handleBoardNodeMemoryAllocationFailure(node->id);
        exit(-1);
    }

    boardNode->current = node;

    return boardNode;
}

void destroyBoardNode(BoardNode* boardNode) {
    free(boardNode);
}

void handleBoardNodeMemoryAllocationFailure(const int boardNodeId) {
    fprintf(stderr, "Failed to allocate %zu bytes for board node with node id: %d\n", sizeof(BoardNode), boardNodeId);
}