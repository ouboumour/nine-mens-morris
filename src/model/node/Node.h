#ifndef NODE_H
#define NODE_H

#include <stdbool.h>

#include "../player/Player.h"

typedef struct{
    int id;
    Player* occupier;
    bool isADestCandidate;
} Node;

Node* createNode(int nodeId);
void destroyNode(Node* node);

void setAsDestCandidate(Node* node);

#endif //NODE_H