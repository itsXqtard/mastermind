#include <stdio.h>
#include <stdlib.h>
#include<time.h>

#define CODE_SIZE 4

typedef struct Boards {
    int code[CODE_SIZE];
    int attempts;
} Board;

typedef struct Arguments {
    char* previous;
    char* current;
    int userSetCFlag;
    int userSetTFlag;
} Argument;

Board initBoardDefault();
int my_atoi(char* str);
void processArguments(Board* board,int argc, char* argv[]);

int main(int argc, char* argv[]) {
    Board my_board = initBoardDefault();
    processArguments(&my_board, argc, argv);

    printf("Board attempts:%d\n", my_board.attempts);


    return 0;


}
/**
 * 
 * Initializes a board with default values
 *
 * Return - Board
 *
**/
Board initBoardDefault() {
    Board board = {};

    //seed the randome generator with current time;
    srand(time(0));
    for(int x = 0; x < CODE_SIZE; x++){
        int random_number = rand() % 4;
        board.code[x] = random_number;
    }
    board.attempts = 10;
    return board;

}

int my_atoi(char* str) {
    int number = 0;
    int index = 0;
    while (str[index] >= '0' && str[index] <= '9')
    {
        // multiply by base 10
        number *= 10;    
        // convet ASCII '0'..'9' to digit 0..9 and add it to number           
        number += str[index] - '0';
        // next character;         
        index++;                     
    }
    return number;

}

void checkFlagArguments(Board* board, Argument argument){
    if(argument.userSetTFlag == 1 && argument.previous[1] == 't') {
        int attempts = my_atoi(argument.current);
        board->attempts = attempts;
    }
    if(argument.userSetCFlag == 1 && argument.previous[1] == 'c') {
        int loop;
        printf("Code: ");
        for(loop = 0; loop < 4; loop++) {
            printf("%c ", argument.current[loop]);
        }
    }
}

void processArguments(Board* board, int argc, char* argv[]) {
    Argument arg = {"", "", 0, 0};
    // int userSetAttempts = 0;
    // int userSetCode = 0;
    int x = 1;
    for(; x <argc; x++){
        arg.current = argv[x];
        if(arg.current[0] == '-'){
            switch(arg.current[1]) {
                case 't' :
                    arg.userSetTFlag = 1;
                    break;
                case 'c' :
                    arg.userSetCFlag = 1;
                    break;
                default :
                    printf("Invalid command\n" );
            }
        }
        arg.previous = argv[x - 1]; 
        checkFlagArguments(board, arg);        
    }  
}