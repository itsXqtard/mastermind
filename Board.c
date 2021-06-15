#include "Board.h"

/**
 * Checks if a character is in the input string
 * @param  str - string to iterate through
 * @param  c   - character to look for in string
 * @return     - index of first occurrence of character
 *               in string    
**/
static int findFirstOccurrence(char* s, char c) {
    int x = 0;
    while(*s != '\0') {
        if(*s == c) {
            return x;
        }
        s++;
        x++;
    }
    return -1;
}
/**
 * Marks the board for all exact pieces
 * @param  board        - contains information about game's board 
 *                        like entry to mark all users attempt for that round
 * @param  userGuess    - Users inputted attempt at finding code   
**/
static void markXPieces(Board* board, char* userGuess) {
    for(int x = 0; x < CODE_SIZE; x++) {
        char code = board->code[x] + '0';
        if(code == userGuess[x]) {
            board->markedBoard[x] = EXACT;
            continue;
        }
        board->markedBoard[x] = code;
    }
}
/**
 * Marks the board for all misplaced pieces
 * @param  board        - contains information about game's board 
 *                        like entry to mark all users attempt for that round
 * @param  userGuess    - Users inputted attempt at finding code   
**/
static void markMPieces(Board* board, char* userGuess) {
    for(int x = 0; x < CODE_SIZE; x++) {
        int index = findFirstOccurrence(board->markedBoard, userGuess[x]);
        if(board->markedBoard[x] != EXACT &&index >= 0) {
            board->markedBoard[index] = MISPLACED;
        }
    }
}

/**
 * Marks board position with all pieces that are well placed
 * and missplaced
 * @param  board        - contains information about game's board 
 *                        like entry to mark all users attempt for that round
 * @param  userGuess    - Users inputted attempt at finding code
 * @return              - a string that contains all marked places for well placed
 *                        and misplaced pieces.    
**/
static char* markPieces(Board* board, char* userGuess) {
    markXPieces(board, userGuess);
    markMPieces(board, userGuess);
    return board->markedBoard;
}

/**
 *
 * Returns PlacedPieces with counts of exact placements
 * and all missplacements.
 * @param  markedBoard   - used to mark places in the board
 * @return               - returns PlacedPiece that contains count of well placed 
 *.                        and missplaced pieces.
 *
**/
static PlacedPiece countMarkedPieces(char* markedBoard) {
    PlacedPiece placedPieces = {0, 0};
    for(int index = 0; index < CODE_SIZE; index++) {
        if(markedBoard[index] == EXACT) {
            placedPieces.wellPlaced++;
        }
        if(markedBoard[index] == MISPLACED) {
            placedPieces.missPlaced++;
        }
    }
    return placedPieces;
}

/** 

NON STATIC METHODS 

**/

/**
 * Prints a formated statement indicaing all the well placed and misplaced pieces
 * @param  pieces        - contains information about the counts of well placed
**/
void printPlacedPieces(PlacedPiece pieces) {
    printf("Well placed pieces %d\n", pieces.wellPlaced);
    printf("Misplaced pieces %d\n", pieces.missPlaced);
}

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
PlacedPiece checkUserInput(Board* board, char* userGuess) {
    char* markedPieces = markPieces(board, userGuess);
    return countMarkedPieces(markedPieces);
}


/**
 * Initializes a board with default values
 * @return - Board
**/
Board initBoardDefault() {
    Board board = {};

    //seed the randome generator with current time;
    srand(time(0));
    for(int x = 0; x < CODE_SIZE; x++){
        int random_number = rand() % MAX_PIECES + 1;
        board.code[x] = random_number;
    }
    board.markedBoard[CODE_SIZE] = '\0';
    board.attempts = 10;
    return board;

}