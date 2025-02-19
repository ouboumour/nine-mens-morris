#ifndef RESERVEBAR_H
#define RESERVEBAR_H

#include "../../utils/commons/Commons.h"

typedef struct {
    char* id;
    Coordinates coordinates;
    int reserve;
} ReserveBar;

void renderReserveBar(ReserveBar bar);

#endif //RESERVEBAR_H