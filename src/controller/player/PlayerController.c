#include "PlayerController.h"

#include <stdio.h>
#include <arm/limits.h>

#include "../../model/board/Board.h"
#include "../../model/game/Game.h"
#include "../game/GameController.h"

#include <float.h>
#include <time.h>

void switchPlayer();
void decrementPlayerReserve();
void incrementPlayerPlacedPeaces();
void decrementOponnentPlacedPeaces();
void refreshGamePhase(const Node* currentNode);
void placeNode(Node* node);

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

void incrementPlayerPlacedPeaces() {
    if (game.players[game.currentPlayerId-1].placedPieces == 9) return;
    game.players[game.currentPlayerId-1].placedPieces++;
}

void decrementOponnentPlacedPeaces() {
    if (game.players[game.currentPlayerId%2].placedPieces == 0) return;
    game.players[game.currentPlayerId%2].placedPieces--;
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











static double evaluateBoardState() {
    // Example: difference in placedPieces
    Player* me  = getCurrentPlayer();
    Player* opp = &game.players[ (game.currentPlayerId % 2) ];
    return (double)(me->placedPieces) - (double)(opp->placedPieces);
}

static bool isGameOverForMinimax() {
    // If current player is stuck or has <3 pieces => game is over
    // Or use your own logic: if(isGameOver()) return true, etc.
    if (isPlayerStuck(getCurrentPlayer()) || didPlayerLoseTooMuchPieces(getCurrentPlayer())) {
        return true;
    }
    return false;
}

static clock_t searchStart = 0;

static double timeLimitSeconds = 2.0;

void startSearchTimer(double limitSeconds) {
    searchStart = clock();           // clock() returns "ticks" since program start
    timeLimitSeconds = limitSeconds; // store the time limit
}


bool isTimeExpired() {
    // time in seconds so far
    double elapsed = (double)(clock() - searchStart) / CLOCKS_PER_SEC;
    return elapsed >= timeLimitSeconds;
}


static double minimax(int depth, double alpha, double beta, bool maximizingPlayer) {
    if (isTimeExpired()) {
        return evaluateBoardState();
    }


    // Base conditions
    if (depth == 0 || isGameOverForMinimax()) {
        return evaluateBoardState();
    }

    double bestScore = maximizingPlayer ? -DBL_MAX : DBL_MAX;

    // Backup the relevant global state to restore later
    GamePhase oldPhase = game.phase;
    int       oldPlayerId = game.currentPlayerId;
    bool      oldIsOver   = game.isOver;

    // Also back up players array, because placeNode/moveNode/attackNode
    // may change piecesReserve or placedPieces
    Player oldPlayers[2];
    oldPlayers[0] = game.players[0];
    oldPlayers[1] = game.players[1];

    Player* current = getCurrentPlayer();
    Player* opponent = &game.players[ (oldPlayerId % 2) ];

    // Gather nodes for convenience
    Node* myPieces[24];   int myCount = 0;
    Node* emptyNodes[24]; int emptyCount = 0;
    Node* oppNodes[24];   int oppCount = 0;

    // Suppose you have 24 nodes total
    for(int i = 0; i < 24; i++) {
        Node* n = getBoardNodes()[i]; // adjust if you store differently
        if (n->occupier == current) {
            myPieces[myCount++] = n;
        } else if (n->occupier == opponent) {
            oppNodes[oppCount++] = n;
        } else if (n->occupier == NULL) {
            emptyNodes[emptyCount++] = n;
        }
    }

    // Now, based on phase, try moves
    if (game.phase == PLACEMENT) {
        // For each empty node
        for(int i = 0; i < emptyCount; i++){
            Node* dest = emptyNodes[i];

            // Save occupant (should be NULL) & player's counters
            Player* oldOccupier = dest->occupier; // probably NULL
            int oldReserve = current->piecesReserve;
            int oldPlaced  = current->placedPieces;

            // apply
            placeNode(dest);

            // Recurse
            double val;
            if (!game.isOver && depth > 0) {
                val = minimax(depth - 1, alpha, beta, !maximizingPlayer);
            } else {
                // If game ended right away or no depth left
                val = evaluateBoardState();
            }

            // Undo
            dest->occupier = oldOccupier;
            current->piecesReserve = oldReserve;
            current->placedPieces  = oldPlaced;
            game.isOver = oldIsOver;
            game.phase  = oldPhase;
            game.currentPlayerId = oldPlayerId;
            game.players[0] = oldPlayers[0];
            game.players[1] = oldPlayers[1];

            // Track alpha/beta
            if (maximizingPlayer) {
                if (val > bestScore) bestScore = val;
                if (val > alpha) alpha = val;
                if (alpha >= beta) break; // prune
            } else {
                if (val < bestScore) bestScore = val;
                if (val < beta) beta = val;
                if (alpha >= beta) break; // prune
            }
        }
    }
    else if (game.phase == MOVEMENT) {
        // For each of my pieces as source
        for(int i = 0; i < myCount; i++){
            Node* src = myPieces[i];
            markNodeDestinationCandidates(src);

            Node* candidates[24];
            int cCount = 0;
            for(int c = 0; c < 24; c++){
                if(getBoardNodes()[c]->isADestCandidate){
                    candidates[cCount++] = getBoardNodes()[c];
                }
            }

            // For each destination candidate
            for(int k = 0; k < cCount; k++){
                Node* dest = candidates[k];

                // Save old occupant
                Player* oldSrcOcc  = src->occupier;
                Player* oldDestOcc = dest->occupier;

                // Apply
                moveNode(dest);

                double val;
                if (!game.isOver && depth > 0) {
                    val = minimax(depth - 1, alpha, beta, !maximizingPlayer);
                } else {
                    val = evaluateBoardState();
                }

                // Undo
                src->occupier  = oldSrcOcc;
                dest->occupier = oldDestOcc;
                game.isOver    = oldIsOver;
                game.phase     = oldPhase;
                game.currentPlayerId = oldPlayerId;
                game.players[0] = oldPlayers[0];
                game.players[1] = oldPlayers[1];

                if (maximizingPlayer) {
                    if (val > bestScore) bestScore = val;
                    if (val > alpha) alpha = val;
                    if (alpha >= beta) { clearMarkDestinationCandidates(); break; }
                } else {
                    if (val < bestScore) bestScore = val;
                    if (val < beta) beta = val;
                    if (alpha >= beta) { clearMarkDestinationCandidates(); break; }
                }
            }
            clearMarkDestinationCandidates();
        }
    }
    else if (game.phase == ATTACK) {
        // For each opponent piece
        for(int i = 0; i < oppCount; i++){
            Node* target = oppNodes[i];
            Player* oldOcc = target->occupier;

            // Apply
            attackNode(target);

            double val;
            if (!game.isOver && depth > 0) {
                val = minimax(depth - 1, alpha, beta, !maximizingPlayer);
            } else {
                val = evaluateBoardState();
            }

            // Undo
            target->occupier = oldOcc;
            game.isOver = oldIsOver;
            game.phase  = oldPhase;
            game.currentPlayerId = oldPlayerId;
            game.players[0] = oldPlayers[0];
            game.players[1] = oldPlayers[1];

            if (maximizingPlayer) {
                if (val > bestScore) bestScore = val;
                if (val > alpha) alpha = val;
                if (alpha >= beta) break;
            } else {
                if (val < bestScore) bestScore = val;
                if (val < beta) beta = val;
                if (alpha >= beta) break;
            }
        }
    }

    return bestScore;
}




#include <float.h> // For DBL_MAX
#include <stdbool.h>
#include <stdio.h>

/**
 * Helper to update the "best move" if val is better than bestEval.
 * In C, we have to pass pointers to bestEval, bestSrc, bestDest so we can modify them.
 */
static void updateBestMoveIfNeeded(double val,
                                   Node* src,
                                   Node* dest,
                                   double* bestEval,
                                   Node** bestSrc,
                                   Node** bestDest)
{
    if (val > *bestEval) {
        *bestEval   = val;
        *bestSrc    = src;
        *bestDest   = dest;
    }
}

void performAiMove(int depth, double timout) {

    startSearchTimer(timout);

    if (isGameOver()) return; // or your own check

    bool   maximizingPlayer = true;
    double alpha            = -DBL_MAX;
    double beta             =  DBL_MAX;
    double bestEval         = -DBL_MAX;

    Node* bestSrc          = NULL; // For movement source
    Node* bestDest         = NULL; // For placement/movement dest or attacked node

    // Backup global states
    GamePhase oldPhase    = game.phase;
    int       oldPlayerId = game.currentPlayerId;
    bool      oldIsOver   = game.isOver;

    Player oldPlayers[2];
    oldPlayers[0] = game.players[0];
    oldPlayers[1] = game.players[1];

    Player* current = getCurrentPlayer();
    Player* opp     = &game.players[ (game.currentPlayerId % 2) ];

    // Gather node info
    Node* myPieces[24];   int myCount = 0;
    Node* emptyNodes[24]; int emptyCount = 0;
    Node* oppNodes[24];   int oppCount = 0;

    for (int i = 0; i < 24; i++) {
        Node* n = getBoardNodes()[i]; // Adjust if your board is stored differently
        if      (n->occupier == current) myPieces[myCount++]   = n;
        else if (n->occupier == opp)     oppNodes[oppCount++]   = n;
        else                             emptyNodes[emptyCount++] = n;
    }

    // Explore each possible move in the current phase, just like in minimax.
    if (game.phase == PLACEMENT) {
        for (int i = 0; i < emptyCount; i++) {
            Node* dest = emptyNodes[i];

            // Save occupant & player's data
            Player* oldOcc    = dest->occupier; // likely NULL
            int oldReserve    = current->piecesReserve;
            int oldPlaced     = current->placedPieces;
            bool wasOver      = game.isOver;

            placeNode(dest);

            double val;
            if (!game.isOver && depth > 0) {
                val = minimax(depth - 1, alpha, beta, !maximizingPlayer);
            } else {
                val = evaluateBoardState();
            }

            // Undo
            dest->occupier          = oldOcc;
            current->piecesReserve  = oldReserve;
            current->placedPieces   = oldPlaced;
            game.isOver             = wasOver;
            game.phase              = oldPhase;
            game.currentPlayerId    = oldPlayerId;
            game.players[0]         = oldPlayers[0];
            game.players[1]         = oldPlayers[1];

            // Update best move
            if (val > bestEval) {
                bestEval  = val;
                bestSrc   = NULL;  // No src for placement
                bestDest  = dest;
            }
            if (val > alpha) alpha = val;
            if (alpha >= beta) break;
        }
    }
    else if (game.phase == MOVEMENT) {
        for (int i = 0; i < myCount; i++) {
            Node* src = myPieces[i];

            clearMarkDestinationCandidates();
            markNodeDestinationCandidates(src);

            Node* cands[24];
            int cCount = 0;
            for (int c = 0; c < 24; c++) {
                if (getBoardNodes()[c]->isADestCandidate) {
                    cands[cCount++] = getBoardNodes()[c];
                }
            }

            for (int c = 0; c < cCount; c++) {
                Node* dest = cands[c];

                Player* oldSrcOcc  = src->occupier;
                Player* oldDestOcc = dest->occupier;
                bool    wasOver    = game.isOver;

                Player p0  = game.players[0];
                Player p1  = game.players[1];
                GamePhase oldPh = game.phase;
                int oldPid = game.currentPlayerId;

                moveNode(dest);

                double val;
                if (!game.isOver && depth > 0) {
                    val = minimax(depth - 1, alpha, beta, !maximizingPlayer);
                } else {
                    val = evaluateBoardState();
                }

                // Undo
                src->occupier        = oldSrcOcc;
                dest->occupier       = oldDestOcc;
                game.isOver          = wasOver;
                game.players[0]      = p0;
                game.players[1]      = p1;
                game.phase           = oldPh;
                game.currentPlayerId = oldPid;

                if (val > bestEval) {
                    bestEval  = val;
                    bestSrc   = src;
                    bestDest  = dest;
                }
                if (val > alpha) alpha = val;
                if (alpha >= beta) {
                    clearMarkDestinationCandidates();
                    break;
                }
            }
            clearMarkDestinationCandidates();
        }
    }
    else if (game.phase == ATTACK) {
        for (int i = 0; i < oppCount; i++) {
            Node* target = oppNodes[i];

            Player* oldOcc = target->occupier;
            bool wasOver   = game.isOver;

            Player p0  = game.players[0];
            Player p1  = game.players[1];
            GamePhase oldPh = game.phase;
            int oldPid = game.currentPlayerId;

            attackNode(target);

            double val;
            if (!game.isOver && depth > 0) {
                val = minimax(depth - 1, alpha, beta, !maximizingPlayer);
            } else {
                val = evaluateBoardState();
            }

            // Undo
            target->occupier      = oldOcc;
            game.isOver           = wasOver;
            game.players[0]       = p0;
            game.players[1]       = p1;
            game.phase            = oldPh;
            game.currentPlayerId  = oldPid;

            if (val > bestEval) {
                bestEval = val;
                bestSrc  = NULL;    // No src
                bestDest = target;  // Attack target
            }
            if (val > alpha) alpha = val;
            if (alpha >= beta) break;
        }
    }

    // Finally, actually perform the best move for real:
    if (!bestDest && !bestSrc) {
        // No move found or game is over
        return;
    }

    // According to the phase, do the right call
    if (game.phase == PLACEMENT) {
        placeNode(bestDest);
    }
    else if (game.phase == MOVEMENT) {
        if (bestSrc && bestDest) {
            clearMarkDestinationCandidates();
            markNodeDestinationCandidates(bestSrc);
            moveNode(bestDest);
        }
    }
    else if (game.phase == ATTACK) {
        attackNode(bestDest);
    }
}