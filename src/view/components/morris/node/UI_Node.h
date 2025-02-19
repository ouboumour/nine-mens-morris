#ifndef UI_NODE_H
#define UI_NODE_H

#include <stdbool.h>

#include "../../utils/commons/Commons.h"
#include "../../../../controller/board/BoardController.h"

typedef struct {
    Node* node;
    Coordinates coordinates;
} UI_Node;

void renderNode(UI_Node node);
bool isMouseOverNode(UI_Node piece);

#endif //UI_NODE_H
