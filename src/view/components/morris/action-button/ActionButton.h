#ifndef ACTIONBUTTON_H
#define ACTIONBUTTON_H

#include <stdbool.h>

#include "../commons/Commons.h"

typedef void (*OnClick)();

typedef struct {
    char* id;
    Coordinates coordinates;
    Dimensions dimensions;
    OnClick onClick;
} ActionButton;

void renderActionButton(ActionButton button);
bool isMouseOverActionButton(ActionButton button);

#endif //ACTIONBUTTON_H
