#include "my_mastermind.h"
#ifndef BOARD
#define BOARD

/**
 *
 * Container for holding information about the Board
 *
**/
typedef struct Boards {
    int code[CODE_SIZE];
    int attempts;
    char markedBoard[CODE_SIZE + 1];
} Board;

/**
 *
 * Container for holding information about the User's placement of pieces
 *
**/
typedef struct PlacedPieces {
    int wellPlaced;
    int missPlaced;
} PlacedPiece;


Board initBoardDefault();
PlacedPiece checkUserInput(Board* board, char* userGuess);
void printPlacedPieces(PlacedPiece pieces);

#endif