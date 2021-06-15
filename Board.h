#include "my_mastermind.h"
#ifndef BOARD
#define BOARD


typedef struct Boards {
    int code[CODE_SIZE];
    int attempts;
    char markedBoard[CODE_SIZE + 1];
} Board;


typedef struct PlacedPieces {
    int wellPlaced;
    int missPlaced;
} PlacedPiece;

/**
 * 
 * Initializes a board with default values
 *
 * Return - Board
 *
**/
Board initBoardDefault();
PlacedPiece countMarkedPieces(char* markedBoard);
PlacedPiece checkUserInput(Board* board, char* userGuess);
int contains(char* str, int c);
int findFirstOccurrence(char* s, char c);
char* markPieces(Board* board, char* userGuess);
void markXPieces(Board* board, char* userGuess);
void markMPieces(Board* board, char* userGuess);
void printPlacedPieces(PlacedPiece pieces);

#endif