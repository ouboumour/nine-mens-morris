#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include "../../view/components/morris/node/UI_Node.h"

void placePiece(const UI_Node* uiNode);
void attackPiece(const UI_Node* uiNode);
void movePiece(const UI_Node* uiNode);
void markDestinationCandidates(UI_Node* uiNode);

bool isPlacementPhase();

Player* getFirstPlayer();
Player* getSecondPlayer();
Player* getCurrentPlayer();

void performAiMove(int depth, double timout);

#endif //PLAYERCONTROLLER_H
