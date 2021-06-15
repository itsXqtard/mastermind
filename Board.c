#include "Board.h"


int contains(char* str, int c)
{
    while(*str != '\0') {
        //convert to character and compare
        if(*str == (c + '0')){
            return 1;
        }
        str++;
    }
    return 0;

}

void printPlacedPieces(PlacedPiece pieces) {
    printf("Well placed pieces %d\n", pieces.wellPlaced);
    printf("Misplaced pieces %d\n", pieces.missPlaced);
}


int findFirstOccurrence(char* s, char c) {
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

void markXPieces(Board* board, char* userGuess) {
    for(int x = 0; x < CODE_SIZE; x++) {
        char code = board->code[x] + '0';
        if(code == userGuess[x]) {
            board->markedBoard[x] = EXACT;
            continue;
        }
        board->markedBoard[x] = code;
    }
}

void markMPieces(Board* board, char* userGuess){
    for(int x = 0; x < CODE_SIZE; x++) {
        int index = findFirstOccurrence(board->markedBoard, userGuess[x]);
        if(board->markedBoard[x] != EXACT &&index >= 0) {
            board->markedBoard[index] = MISPLACED;
        }
    }
}

char* markPieces(Board* board, char* userGuess) {
    markXPieces(board, userGuess);
    markMPieces(board, userGuess);
    return board->markedBoard;
}

PlacedPiece countMarkedPieces(char* markedBoard) {
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

PlacedPiece checkUserInput(Board* board, char* userGuess) {
    char* markedPieces = markPieces(board, userGuess);
    return countMarkedPieces(markedPieces);
}



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