#include "Board.h"

#define MAX_MILL 3
#define MAX_NEIGHBORS 4

#include <stdio.h>
#include <__stddef_null.h>

#include "../node/Node.h"
#include "../board-node/BoardNode.h"
#include "../game/Game.h"

typedef struct {
    int i;
    int j;
} Position;

Position idToIdx(int nodeId);
void initBoardNodes();
BoardNode* getLeftMostNode(BoardNode* boardNode);

BoardNode* boardNodes[MAX_NODES];

void clearBoard() {
    for (int i = 0; i < MAX_NODES; ++i) {
        clearNode(boardNodes[i]->current);
    }
}

void initBoard() {
    initBoardNodes();
}

BoardNode** getBoardNodesList() {
    return boardNodes;
}

Position idToIdx(const int nodeId) {
    int cavity = 0;
    if (nodeId >= 21) cavity = 3;
    else if (nodeId >= 13) cavity = 2;
    else if (nodeId >= 5) cavity = 1;

    int i = (nodeId-1+cavity) / MAX_MILL % MAX_MILL;
    int j = (nodeId-1+cavity) % MAX_MILL ;
    return (Position){i, j};
}

void initBoardNodes() {
    // init nodes
    for (int i = 0; i < MAX_NODES; ++i) {
        boardNodes[i] = createBoardNode(createNode(i+1));
    }

    // init navigators
    boardNodes[0]->navigator = (NodeNavigator){NULL, boardNodes[1], boardNodes[3], NULL};
    boardNodes[1]->navigator = (NodeNavigator){NULL, boardNodes[2], boardNodes[9], boardNodes[0]};
    boardNodes[2]->navigator = (NodeNavigator){NULL, NULL, boardNodes[4], boardNodes[1]};
    boardNodes[3]->navigator = (NodeNavigator){boardNodes[0], boardNodes[11], boardNodes[5], NULL};
    boardNodes[4]->navigator = (NodeNavigator){boardNodes[2], NULL, boardNodes[7], boardNodes[12]};
    boardNodes[5]->navigator = (NodeNavigator){boardNodes[3], boardNodes[6], NULL, NULL};
    boardNodes[6]->navigator = (NodeNavigator){boardNodes[14], boardNodes[7], NULL, boardNodes[5]};
    boardNodes[7]->navigator = (NodeNavigator){boardNodes[4], NULL, NULL, boardNodes[6]};

    boardNodes[8]->navigator = (NodeNavigator){NULL, boardNodes[9], boardNodes[11], NULL};
    boardNodes[9]->navigator = (NodeNavigator){boardNodes[1], boardNodes[10], boardNodes[17], boardNodes[8]};
    boardNodes[10]->navigator = (NodeNavigator){NULL, NULL, boardNodes[12], boardNodes[9]};
    boardNodes[11]->navigator = (NodeNavigator){boardNodes[8], boardNodes[19], boardNodes[13], boardNodes[3]};
    boardNodes[12]->navigator = (NodeNavigator){boardNodes[10], boardNodes[4], boardNodes[15], boardNodes[20]};
    boardNodes[13]->navigator = (NodeNavigator){boardNodes[11], boardNodes[14], NULL, NULL};
    boardNodes[14]->navigator = (NodeNavigator){boardNodes[22], boardNodes[15], boardNodes[6], boardNodes[13]};
    boardNodes[15]->navigator = (NodeNavigator){boardNodes[12], NULL, NULL, boardNodes[14]};


    boardNodes[16]->navigator = (NodeNavigator){NULL, boardNodes[17], boardNodes[19], NULL};
    boardNodes[17]->navigator = (NodeNavigator){boardNodes[9], boardNodes[18], NULL, boardNodes[16]};
    boardNodes[18]->navigator = (NodeNavigator){NULL, NULL, boardNodes[20], boardNodes[17]};
    boardNodes[19]->navigator = (NodeNavigator){boardNodes[16], NULL, boardNodes[21], boardNodes[11]};
    boardNodes[20]->navigator = (NodeNavigator){boardNodes[18], boardNodes[12], boardNodes[23], NULL};
    boardNodes[21]->navigator = (NodeNavigator){boardNodes[19], boardNodes[22], NULL, NULL};
    boardNodes[22]->navigator = (NodeNavigator){NULL, boardNodes[23], boardNodes[14], boardNodes[21]};
    boardNodes[23]->navigator = (NodeNavigator){boardNodes[20], NULL, NULL, boardNodes[22]};
}

bool haveSameOccupier(const BoardNode* boardNode1, const BoardNode* boardNode2) {
    if (boardNode1 == NULL || boardNode2 == NULL ||
        boardNode1->current == NULL || boardNode2->current == NULL ||
        boardNode1->current->occupier ==NULL || boardNode2->current->occupier == NULL)
        return false;
    return boardNode1->current->occupier == boardNode2->current->occupier;
}

BoardNode* getLeftMostNode(BoardNode* boardNode) {
    BoardNode* leftMostNode = boardNode;
    while (leftMostNode->navigator.left != NULL) {
        leftMostNode = leftMostNode->navigator.left;
    }
    return leftMostNode;
}

BoardNode* getTopMostNode(BoardNode* boardNode) {
    BoardNode* topMostNode = boardNode;
    while (topMostNode->navigator.top != NULL) {
        topMostNode = topMostNode->navigator.top;
    }
    return topMostNode;
}

bool belongsToHorizontalMill(BoardNode* boardNode) {
    const BoardNode* leftNode = getLeftMostNode(boardNode);
    const BoardNode* middleNode = leftNode->navigator.right;
    const BoardNode* rightNode = middleNode->navigator.right;
    return haveSameOccupier(leftNode, middleNode) && haveSameOccupier(middleNode, rightNode);
}

bool belongsToVerticalMill(BoardNode* boardNode) {
    const BoardNode* topNode = getTopMostNode(boardNode);
    const BoardNode* middleNode = topNode->navigator.bottom;
    const BoardNode* bottomNode = middleNode->navigator.bottom;
    return haveSameOccupier(topNode, middleNode) && haveSameOccupier(middleNode, bottomNode);
}

BoardNode* toBoardNode(const Node* node) {
    return boardNodes[node->id-1];
}

bool belongsToMill(const Node* node) {
    if (node == NULL || node->occupier == NULL) return false;
    BoardNode* boardNode = toBoardNode(node);
    return belongsToHorizontalMill(boardNode) || belongsToVerticalMill(boardNode);
}

BoardNode** findAllBoardNodes() {
    return boardNodes;
}

void clearMarkDestinationCandidates() {
    for (int i = 0; i < MAX_NODES; ++i) {
        boardNodes[i]->current->isADestCandidate = false;
    }
}

bool isFreeNode(const BoardNode* boardNode) {
    return boardNode != NULL && boardNode->current->occupier == NULL;
}

void markAsDestCandidateIfFree(const BoardNode* boardNode) {
    if (isFreeNode(boardNode)) setAsDestCandidate(boardNode->current);
}

void markFreeNeighborsCandidates(const BoardNode* boardNode) {
    markAsDestCandidateIfFree(boardNode->navigator.top);
    markAsDestCandidateIfFree(boardNode->navigator.right);
    markAsDestCandidateIfFree(boardNode->navigator.bottom);
    markAsDestCandidateIfFree(boardNode->navigator.left);
}

void markFreeCandidates() {
    for (int i = 0; i < MAX_NODES; ++i) {
        markAsDestCandidateIfFree(boardNodes[i]);
    }
}

void doMarkDestinationCandidates(const Node* node) {
    if (game.players[game.currentPlayerId-1].placedPieces == 3) markFreeCandidates();
    else markFreeNeighborsCandidates(toBoardNode(node));
}

bool isBoardNodeStuck(const BoardNode* boardNode) {
    if (game.players[game.currentPlayerId-1].placedPieces == 3) return false;
    return !isFreeNode(boardNode->navigator.top) &&
           !isFreeNode(boardNode->navigator.right) &&
           !isFreeNode(boardNode->navigator.bottom) &&
           !isFreeNode(boardNode->navigator.left);
}