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

/**
 * Initializes a board with default values
 * @return - Board
**/
Board initBoardDefault();
/**
 *
 * Returns PlacedPieces with counts of exact placements
 * and all missplacements.
 * @param  markedBoard   - used to mark places in the board
 * @return               - returns PlacedPiece that contains count of well placed 
 *.                        and missplaced pieces.
 *
**/
PlacedPiece countMarkedPieces(char* markedBoard);
/**
 *
 * Checks users input and with the board's codes for all well placed and 
 * misplaced pieces.
 * @param  board         - contains information about game's code and attempts
 * @param  userGuess     - users inputted attempt at finding code
 * @return               - returns PlacedPiece that contains count of well placed 
 *                         and missplaced pieces
 *
**/
PlacedPiece checkUserInput(Board* board, char* userGuess);
/**
 * Checks if a character is in the input string
 * @param  str - string to iterate through
 * @param  c   - character to look for in string
 * @return     - 0 or 1 indicating whether character 
 *               was found in string     
**/
int contains(char* str, int c);
/**
 * Checks if a character is in the input string
 * @param  str - string to iterate through
 * @param  c   - character to look for in string
 * @return     - index of first occurrence of character
 *               in string    
**/
int findFirstOccurrence(char* s, char c);
/**
 * Marks board position with all pieces that are well placed
 * and missplaced
 * @param  board        - contains information about game's board 
 *                        like entry to mark all users attempt for that round
 * @param  userGuess    - Users inputted attempt at finding code
 * @return              - a string that contains all marked places for well placed
 *                        and misplaced pieces.    
**/
char* markPieces(Board* board, char* userGuess);
/**
 * Marks the board for all exact pieces
 * @param  board        - contains information about game's board 
 *                        like entry to mark all users attempt for that round
 * @param  userGuess    - Users inputted attempt at finding code   
**/
void markXPieces(Board* board, char* userGuess);
/**
 * Marks the board for all misplaced pieces
 * @param  board        - contains information about game's board 
 *                        like entry to mark all users attempt for that round
 * @param  userGuess    - Users inputted attempt at finding code   
**/
void markMPieces(Board* board, char* userGuess);
/**
 * Prints a formated statement indicaing all the well placed and misplaced pieces
 * @param  pieces        - contains information about the counts of well placed
**/
void printPlacedPieces(PlacedPiece pieces);

#endif