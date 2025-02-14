#ifndef POPUP_H
#define POPUP_H

#include "../commons/Commons.h"

typedef struct {
    char* id;
    Coordinates coordinates;
} Popup;

void renderPopup(Popup popup);

#endif //POPUP_H