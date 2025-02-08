#ifndef UI_PLAYER_H
#define UI_PLAYER_H

#include "../reserve-bar/ReserveBar.h"

typedef struct {
    int id;
    char* pseudo;
    ReserveBar* reserveBar;
} UI_Player;

// toUiPlayer(Player* player);

#endif //UI_PLAYER_H