#ifndef TEXTBUTTON_H
#define TEXTBUTTON_H

#include <stdbool.h>

#include "../../utils/commons/Commons.h"

typedef void (*OnClick)();

typedef enum {
    FLAT_BUTTON,
    DIRECTED_BUTTON
} ButtonType;

typedef struct {
    char* id;
    char* label;
    ButtonType type;
    Coordinates coordinates;
    Dimensions dimensions;
    OnClick onClick;
} TextButton;

void renderTextButton(TextButton button);
bool isMouseOverTextButton(TextButton button);

#endif //TEXTBUTTON_H