#include "Board.h"

#define MAX_NODES 24
#define MAX_MILL 3
#define MAX_NEIGHBORS 4

#include <stdio.h>
#include <__stddef_null.h>

#include "../node/Node.h"
#include "../boardnode/BoardNode.h"

typedef struct {
    int i;
    int j;
} Position;

// void initNodes();
// void initNodeSquares();
// void initNodeArray();
Position idToIdx(int nodeId);
// Node* (*findSquareByNodeId(int id))[MAX_MILL];
void initBoardNodes();
BoardNode* getLeftMostNode(BoardNode* boardNode);

// Node* outerSquare[MAX_MILL][MAX_MILL];
// Node* middleSquare[MAX_MILL][MAX_MILL];
// Node* innerSquare[MAX_MILL][MAX_MILL];

// Node* nodes[MAX_NODES];
BoardNode* boardNodes[MAX_NODES];

void initBoard() {
    // initNodes();
    initBoardNodes();
    // showNodes();
}

// void initNodes() {
    // initNodeSquares();
    // initNodeArray();
// }

// void initNodeSquares() {
//     bool doFixCavity = false;
//     for (int i = 0; i < MAX_MILL; ++i) {
//         for (int j = 0; j < MAX_MILL; ++j) {
//             const int startId = i * MAX_MILL + j + 1 - doFixCavity;
//             outerSquare[i][j] = i == 1 && j == 1 ? NULL : createNode(startId, NULL);
//             middleSquare[i][j] = i == 1 && j == 1 ? NULL : createNode(startId + 8, NULL);
//             innerSquare[i][j] = i == 1 && j == 1 ? NULL : createNode(startId + 16, NULL);
//             if (i == 1 && j == 1) doFixCavity = true;
//         }
//     }
// }
//
// void initNodeArray() {
//     for (int i = 0; i < MAX_MILL; ++i) {
//         for (int j = 0; j < MAX_MILL; ++j) {
//             if (i == 1 && j == 1) continue;
//             nodes[outerSquare[i][j]->id-1] = outerSquare[i][j];
//             nodes[middleSquare[i][j]->id-1] = middleSquare[i][j];
//             nodes[innerSquare[i][j]->id-1] = innerSquare[i][j];
//         }
//     }
// }

BoardNode** getBoardNodesList() {
    return boardNodes;
}
//
// Node** getNodesV1() {
//     return nodes;
// }
//
// bool belongsToMillV1(const Node* node) {
//     if (node == NULL) return false;
//     const Position p = idToIdx(node->id);
//     Node* (*square)[MAX_MILL] = findSquareByNodeId(node->id);
//     if ((p.i+p.j) %2 == 1) {
//         if (outerSquare[p.i][p.j]->occupier == middleSquare[p.i][p.j]->occupier &&  middleSquare[p.i][p.j]->occupier == innerSquare[p.i][p.j]->occupier) return true;
//         if (p.i==1) return square[p.i][p.j]->occupier == square[p.i-1][p.j]->occupier && square[p.i-1][p.j]->occupier == square[p.i+1][p.j]->occupier;
//         return square[p.i][p.j]->occupier == square[p.i][p.j-1]->occupier && square[p.i][p.j-1]->occupier == square[p.i][p.j+1]->occupier;
//     }
//     if (p.i==0) return (square[0][0]->occupier == square[0][1]->occupier && square[0][1]->occupier == square[0][2]->occupier) || (square[p.i][p.j]->occupier == square[p.i+1][p.j]->occupier && square[p.i+1][p.j]->occupier == square[p.i+2][p.j]->occupier);
//     return (square[2][0]->occupier == square[2][1]->occupier && square[2][1]->occupier == square[2][2]->occupier) || (square[p.i][p.j]->occupier == square[p.i-1][p.j]->occupier && square[p.i-1][p.j]->occupier == square[p.i-2][p.j]->occupier);
// }

Position idToIdx(const int nodeId) {
    int cavity = 0;
    if (nodeId >= 21) cavity = 3;
    else if (nodeId >= 13) cavity = 2;
    else if (nodeId >= 5) cavity = 1;

    int i = (nodeId-1+cavity) / MAX_MILL % MAX_MILL;
    int j = (nodeId-1+cavity) % MAX_MILL ;
    return (Position){i, j};
}

// Node* (*findSquareByNodeId(const int id))[MAX_MILL] {
//     if (id <= 8) return outerSquare;
//     if (id <= 16) return middleSquare;
//     return innerSquare;
// }

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


void markNodeAsDestCandidate(const BoardNode* boardNode) {
    if (boardNode == NULL) return;
    if (boardNode->current->occupier == NULL) setAsDestCandidate(boardNode->current);
}

void doMarkDestinationCandidates(const Node* node) {
    const BoardNode* boardNode = toBoardNode(node);
    markNodeAsDestCandidate(boardNode->navigator.top);
    markNodeAsDestCandidate(boardNode->navigator.right);
    markNodeAsDestCandidate(boardNode->navigator.bottom);
    markNodeAsDestCandidate(boardNode->navigator.left);
}