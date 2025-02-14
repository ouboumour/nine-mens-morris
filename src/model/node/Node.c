#include "Node.h"

#include <stdio.h>
#include <stdlib.h>

void handleNodeMemoryAllocationFailure(int nodeId);

Node* createNode(const int nodeId) {
    Node* node = malloc(sizeof(Node));

    if (node == NULL) {
        handleNodeMemoryAllocationFailure(nodeId);
        exit(-1);
    }

    node->id = nodeId;
    node->occupier = NULL;
    node->isADestCandidate = false;

    return node;
}

void destroyNode(Node* node) {
    free(node);
}

void handleNodeMemoryAllocationFailure(const int nodeId) {
    fprintf(stderr, "Failed to allocate %zu bytes for node with id: %d\n", sizeof(Node), nodeId);
}

void setAsDestCandidate(Node* node) {
    node->isADestCandidate = true;
}

void clearNode(Node* node) {
    node->occupier = NULL;
    node->isADestCandidate = false;
}