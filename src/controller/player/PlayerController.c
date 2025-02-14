#include "PlayerController.h"

#include <stdio.h>
#include <arm/limits.h>

#include "../../model/board/Board.h"
#include "../../model/game/Game.h"
#include "../../view/pages/play-page/playPageView.h"


#define max(x,y) (((x) >= (y)) ? (x) : (y))
#define min(x,y) (((x) <= (y)) ? (x) : (y))

void switchPlayer();
void decrementPlayerReserve();
void incrementPlayerPlacedPeaces();
void decrementOponnentPlacedPeaces();
void refreshGamePhase(const Node* currentNode);
void placeNode(Node* node);


void undoDecrementOponnentPlacedPeaces();
void undoDecrementPlayerReserve();
void undoIncrementPlayerPlacedPeaces();
void undoPlaceNode(Node* node);

Node* selectedPiece;

void markNodeDestinationCandidates(Node* node) {
    // if clicking on the opponent pieces return
    if (node->occupier != getCurrentPlayer()) return;
    selectedPiece = node;
    clearMarkDestinationCandidates();
    doMarkDestinationCandidates(node);
}

void markDestinationCandidates(UI_Node* uiNode) {
    markNodeDestinationCandidates(uiNode->node);
}

void removeSelectedPiece() {
    selectedPiece->occupier = NULL;
    selectedPiece = NULL;
    getCurrentPlayer()->placedPieces--;
}

void moveNode(Node* destNode) {
    if (!destNode->isADestCandidate) return;

    clearMarkDestinationCandidates();
    removeSelectedPiece();
    placeNode(destNode);
}

void undoMoveNode(Node* node) {
    // if (!node->isADestCandidate) return;

    // clearMarkDestinationCandidates();
    // removeSelectedPiece();
    // undoPlaceNode(node);

    node->occupier = NULL;
    refreshGamePhase(node);

    if (belongsToMill(node)) {
        game.phase = ATTACK;
        return;
    }

    switchPlayer();

    if (isPlayerStuck(getCurrentPlayer()) || didPlayerLoseTooMuchPieces(getCurrentPlayer())) {
        markGameAsOver();
    }

    // refreshGamePhase(NULL);
    refreshGamePhase(node);
}

void movePiece(const UI_Node* uiNode) {
    moveNode(uiNode->node);
}

void placeNode(Node* node) {
    if (node->occupier != NULL) return;
    node->occupier = getCurrentPlayer();

    decrementPlayerReserve();
    incrementPlayerPlacedPeaces();

    refreshGamePhase(node);

    if (belongsToMill(node)) {
        game.phase = ATTACK;
        return;
    }

    switchPlayer();

    if (isPlayerStuck(getCurrentPlayer()) || didPlayerLoseTooMuchPieces(getCurrentPlayer())) {
        markGameAsOver();
    }
}


void undoPlaceNode(Node* node) {
    // if (node->occupier != NULL) return;
    node->occupier = NULL;

    undoDecrementPlayerReserve();
    undoIncrementPlayerPlacedPeaces();

    refreshGamePhase(node);

    if (belongsToMill(node)) {
        game.phase = ATTACK;
        return;
    }

    switchPlayer();

    if (isPlayerStuck(getCurrentPlayer()) || didPlayerLoseTooMuchPieces(getCurrentPlayer())) {
        markGameAsOver();
    }
}

void placePiece(const UI_Node* uiNode) {
    placeNode(uiNode->node);
}

void attackNode(Node* node) {
    if (node->occupier != &game.players[game.currentPlayerId%2]) return;
    if (belongsToMill(node) && hasUnprotectedPieces(node->occupier)) {
        return;
    }
    decrementOponnentPlacedPeaces();
    node->occupier = NULL;
    refreshGamePhase(node);
    switchPlayer();

    if (isPlayerStuck(getCurrentPlayer()) || didPlayerLoseTooMuchPieces(getCurrentPlayer())) {
        markGameAsOver();
    }
}

void undoAttackNode(Node* node) {
    // if (node->occupier != &game.players[game.currentPlayerId%2]) return;
    // if (belongsToMill(node) && hasUnprotectedPieces(node->occupier)) {
        // return;
    // }
    undoDecrementOponnentPlacedPeaces();
    node->occupier = &game.players[game.currentPlayerId%2];
    game.phase = ATTACK;
    switchPlayer();

    if (isPlayerStuck(getCurrentPlayer()) || didPlayerLoseTooMuchPieces(getCurrentPlayer())) {
        markGameAsOver();
    }
}

void attackPiece(const UI_Node* uiNode) {
    attackNode(uiNode->node);
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

void undoDecrementPlayerReserve() {
    if (game.players[game.currentPlayerId-1].piecesReserve == 9) return;
    game.players[game.currentPlayerId-1].piecesReserve++;
}

void incrementPlayerPlacedPeaces() {
    if (game.players[game.currentPlayerId-1].placedPieces == 9) return;
    game.players[game.currentPlayerId-1].placedPieces++;
}

void undoIncrementPlayerPlacedPeaces() {
    if (game.players[game.currentPlayerId-1].placedPieces == 0) return;
    game.players[game.currentPlayerId-1].placedPieces--;
}

void decrementOponnentPlacedPeaces() {
    if (game.players[game.currentPlayerId%2].placedPieces == 0) return;
    game.players[game.currentPlayerId%2].placedPieces--;
}

void undoDecrementOponnentPlacedPeaces() {
    if (game.players[game.currentPlayerId%2].placedPieces == 9) return;
    game.players[game.currentPlayerId%2].placedPieces++;
}


Player* getCurrentPlayer() {
    return &game.players[game.currentPlayerId-1];
}

void refreshGamePhase(const Node* currentNode) {
    if (belongsToMill(currentNode)) {
        game.phase = ATTACK;
    } else if (isPlacementPhase()) {
        game.phase = PLACEMENT;
    } else {
        game.phase = MOVEMENT;
    }
}

int evaluateBoard(int depth) {
    // if (depth == 200) return INT_MIN;
    return getSecondPlayer()->placedPieces - getFirstPlayer()->placedPieces - depth;
}


int maximize(int depth);
int minimize(int depth);

int maximize(int depth) {
    printf("depth=%d\n", depth);
     Node** nodes = getBoardNodes();
    if (game.isOver) {
        // clearGame();
        return evaluateBoard(depth);
    }
    int bestScore = INT_MIN;
    for (int i = 0; i < MAX_NODES; ++i) {
        int score;
        if (game.phase == ATTACK) {
            for (int j = 0; j < MAX_NODES; ++j) {
                if (nodes[j]->occupier == getFirstPlayer()) {
                    if (belongsToMill(nodes[j]) && hasUnprotectedPieces(nodes[j]->occupier)) continue;
                    attackNode(nodes[j]);
                    score = game.currentPlayerId == 2 ? maximize(depth+1) : minimize(depth+1);
                    undoAttackNode(nodes[j]);
                }
            }
        } else if (game.phase == PLACEMENT) {
            if (nodes[i]->occupier != NULL) continue;
            placeNode(nodes[i]);
            score = minimize(depth+1);
            undoPlaceNode(nodes[i]);
        } else {
            if (nodes[i]->occupier != getSecondPlayer()) continue;
            for (int j = 0; j < MAX_NODES; ++j) {
                markNodeDestinationCandidates(nodes[j]);
                for (int k = 0; k < MAX_NODES; ++k) {
                    if (nodes[k]->isADestCandidate) {
                        moveNode(nodes[k]);
                        score = game.currentPlayerId == 2 ? maximize(depth+1) : minimize(depth+1);
                        moveNode(nodes[j]);
                    }
                }
            }
        }
        bestScore = max(bestScore, score);
    }
    return bestScore;
}

int minimize(int depth) {

    initPlayPageView();

    printf("depth=%d\n", depth);
    Node** nodes = getBoardNodes();
     if (game.isOver) {
        // clearGame();
        return evaluateBoard(depth);
    }
    int bestScore = INT_MAX;
    for (int i = 0; i < MAX_NODES; ++i) {
        int score;
        if (game.phase == ATTACK) {
            for (int j = 0; j < MAX_NODES; ++j) {
                if (nodes[j]->occupier == getSecondPlayer()) {
                    if (belongsToMill(nodes[j]) && hasUnprotectedPieces(nodes[j]->occupier)) continue;
                    attackNode(nodes[j]);
                    score = game.currentPlayerId == 2 ? maximize(depth+1) : minimize(depth+1);
                    undoAttackNode(nodes[j]);
                }
            }
        } else if (game.phase == PLACEMENT) {
            if (nodes[i]->occupier != NULL) continue;
            placeNode(nodes[i]);
            score = game.currentPlayerId == 2 ? maximize(depth+1) : minimize(depth+1);
            undoPlaceNode(nodes[i]);
        } else {
            if (nodes[i]->occupier != getFirstPlayer()) continue;
            for (int j = 0; j < MAX_NODES; ++j) {
                markNodeDestinationCandidates(nodes[j]);
                for (int k = 0; k < MAX_NODES; ++k) {
                    if (nodes[k]->isADestCandidate) {
                        moveNode(nodes[k]);
                        score = game.currentPlayerId == 2 ? maximize(depth+1) : minimize(depth+1);
                        moveNode(nodes[j]);
                    }
                }
            }
        }
        bestScore = min(bestScore, score);
    }
    return bestScore;
}

void foo() {
    maximize(0);
}