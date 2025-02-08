#include "PlayerController.h"

#include <stdio.h>

#include "../../model/board/Board.h"
#include "../../model/game/Game.h"

void switchPlayer();
void decrementPlayerReserve();
void incrementPlayerPlacedPeaces();
void decrementOponnentPlacedPeaces();
void refreshGamePhase(const Node* currentNode);

UI_Node* selectedPiece;

void markDestinationCandidates(UI_Node* uiNode) {
    // if clicking on the opponent pieces return
    if (uiNode->node->occupier != getCurrentPlayer()) return;
    selectedPiece = uiNode;
    clearMarkDestinationCandidates();
    doMarkDestinationCandidates(uiNode->node);
}

void removeSelectedPiece() {
    selectedPiece->node->occupier = NULL;
    selectedPiece = NULL;
    getCurrentPlayer()->placedPieces--;
}

void movePiece(const UI_Node* uiNode) {
    if (!uiNode->node->isADestCandidate) return;

    clearMarkDestinationCandidates();
    removeSelectedPiece();
    placePiece(uiNode);
}


void placePiece(const UI_Node* uiNode) {
    if (uiNode->node->occupier != NULL) return;
    uiNode->node->occupier = getCurrentPlayer();

    decrementPlayerReserve();
    incrementPlayerPlacedPeaces();

    refreshGamePhase(uiNode->node);

    if (belongsToMill(uiNode->node)) {
        game.phase = ATTACK;
        return;
    }

    switchPlayer();
}

bool isGameOver() {
    return game.phase == MOVEMENT && (getFirstPlayer()->placedPieces<3 || getSecondPlayer()->placedPieces<3);
}

void attackPiece(const UI_Node* uiNode) {
    if (uiNode->node->occupier == getCurrentPlayer()) return;
    if (belongsToMill(uiNode->node) && hasUnprotectedPieces(uiNode->node->occupier)) {
        return;
    }
    decrementOponnentPlacedPeaces();
    uiNode->node->occupier = NULL;
    refreshGamePhase(NULL);
    if (isGameOver()) printf("Game over! %s wins", getCurrentPlayer()->pseudo);
    switchPlayer();
}

void switchPlayer() {
    game.currentPlayerId = game.currentPlayerId % 2 + 1;
}

Player* getFirstPlayer() {
    return &game.players[0];
}

Player* getSecondPlayer() {
    return &game.players[1];
}

void decrementPlayerReserve() {
    if (game.players[game.currentPlayerId-1].piecesReserve == 0) return;
    game.players[game.currentPlayerId-1].piecesReserve--;
}

void incrementPlayerPlacedPeaces() {
    if (game.players[game.currentPlayerId-1].placedPieces == 9) return;
    game.players[game.currentPlayerId-1].placedPieces++;
}

void decrementOponnentPlacedPeaces() {
    //todo: add game over logic
    if (game.players[game.currentPlayerId%2].placedPieces == 0) return;
    game.players[game.currentPlayerId%2].placedPieces--;
}

Player* getCurrentPlayer() {
    return &game.players[game.currentPlayerId-1];
}

void refreshGamePhase(const Node* currentNode) {
    if (currentNode != NULL && belongsToMill(currentNode)) {
        game.phase = ATTACK;
    } else if (isPlacementPhase()) {
        game.phase = PLACEMENT;
    } else {
        game.phase = MOVEMENT;
    }
}