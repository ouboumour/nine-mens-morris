#ifndef BOARDNODE_H
#define BOARDNODE_H

#include "../node/Node.h"

typedef struct BoardNode BoardNode;

typedef struct {
    BoardNode* top;
    BoardNode* right;
    BoardNode* bottom;
    BoardNode* left;
} NodeNavigator;

typedef struct BoardNode {
    Node* current;
    NodeNavigator navigator;
} BoardNode;

BoardNode* createBoardNode(Node* node);


#endif //BOARDNODE_H