#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

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

    char input[CODE_SIZE];
    Board my_board = initBoardDefault();
    processArguments(&my_board, argc, argv);

    printf("Attempts you have:%d What is your guess?\n", my_board.attempts);
    read(STDIN_FILENO, input, sizeof(input));
    write(STDOUT_FILENO, input, sizeof(input));



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
        int random_number = rand() % CODE_SIZE;
        board.code[x] = random_number;
    }
    board.attempts = 10;
    return board;

}
/**
 * str - a string that contains only digits
 *  
 *  returns positive integer conversion from string
 *  or returns -1 if string contains characters not a digit.
*/
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
    if (!(str[index] >= '0' && str[index] <= '9')) {
        return -1;
    }
    return number;

}
/*
*
*Still does not work..
*/
int* convertStrToArray(char* str){
    int code[CODE_SIZE] = { 0, 0, 0, 0 };
    int* code_ptr = code;
    int index = 0;
    while(*str != '\0'){
        code[index] = 10 * (str[index] - 48);
        str++;
        index++;
    }
    return code_ptr;
}

void checkFlagArguments(Board* board, Argument argument){
    int attempts = my_atoi(argument.current);
    if(argument.userSetTFlag == 1 && argument.previous[1] == 't') {
        //if failed to parce string to int value returns -1;
        if(attempts != -1){
            board->attempts = attempts;
        }
    }
    if(argument.userSetCFlag == 1 && argument.previous[1] == 'c') {
        int index;
        int* code = convertStrToArray(argument.current);
        printf("Code: ");
        for(index = 0; index < CODE_SIZE; index++) {
            // board->code[index] = my_atoi(chartoStr(argument.current[index]));
            printf("%d\n", code[index]);
        }
    }
}

void processArguments(Board* board, int argc, char* argv[]) {
    Argument arg = {"", "", 0, 0};
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