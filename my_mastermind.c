#include "my_mastermind.h"


typedef struct Boards {
    int code[CODE_SIZE];
    int attempts;
} Board;

typedef struct Arguments {
    char* previous;
    char* current;
    int userSetCode;
    int userSetAttempts;
} Argument;

Board initBoardDefault();
void processArguments(Board* board,int argc, char* argv[]);
int isUserAttemptValid(char* code);
void checkUserInput(Board* board, char* userAttempt);

int main(int argc, char* argv[]) {

    char input[CODE_SIZE];
    Board my_board = initBoardDefault();
    processArguments(&my_board, argc, argv);

    printf("Will you find the secret code with %d attempts\n", my_board.attempts);
    int round = 0;
    while(my_board.attempts != 0) {
        printf("---\n");
        printf("Round %d\n", round);
        int size = read(STDIN_FILENO, input, sizeof(input) + 1);
        if (size < 0) {
            continue;
        } 
        int valid = isUserAttemptValid(input);
        if(valid == 0){
            printf("Wrong input!\n");
        } else {
            printf("Valid Input: %c, %c, %c, %c\n", input[0],input[1],input[2],input[3]);
            checkUserInput(&my_board, input);
            my_board.attempts--;
            round++;
        }
    } 

    return 0;


}

void findExactMatches(int boardCode[], char* userCode, char matches[]){
    for(int x = 0; x < CODE_SIZE; x++) {
        if(boardCode[x] != (userCode[x] - '0')) {
            matches[x] = userCode[x];
        }
    }
}

void checkUserInput(Board* board, char* userAttempt) {
    char exactMatches[CODE_SIZE] = {'x', 'x', 'x', 'x'};
    findExactMatches(board->code, userAttempt, exactMatches);
    // int exactCount = 0;
    printf("Matches {");
    for(int x = 0; x < CODE_SIZE; x++) {
        printf("%c", exactMatches[x]);
    }
    printf("}");
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
        int random_number = rand() % MAX_PIECES + 1;
        board.code[x] = random_number;
    }
    board.attempts = 10;
    return board;

}
/**
 * str - a string that contains only digits between 0-limit
 *  
 *  returns positive integer conversion from string
 *  or returns -1 if string contains characters not a digit.
*/
int my_atoi(char* str, int limit) {
    int number = 0;
    int index = 0;
    char max = limit + '0';
    while ((str[index] >= '0' && str[index] <= max) || index < CODE_SIZE)
    {
        // multiply by base 10
        number *= 10;    
        // convet ASCII '0'..limit to digit 0..limit and add it to number           
        number += str[index] - '0';
        // next character;         
        index++;                     
    }
    if(str[index] == '\n' || str[index] == '\0'){
        return number;
    }
    if (!(str[index] >= '0' && str[index] <= max)) {
        return -1;
    }
    return number;
}

/**
 *  Determines whether the value passed to the c flag in command line is valid
 *  checks if -1 is present in code
 *  Return 0 - not valid
 *  Return 1 - valid
 *
*/
int isCFlagArgValid(int* code){
    for(int x = 0; x < CODE_SIZE; x++){
        if(code[x] == -1){
            return 0;
        }
    }
    return 1;
}

/**
 * Determines whether the value inputted by user is valid
 * checks if any of the character are digit values
 * Return 0 - not valid
 * Return 1 - valid
*/
int isUserAttemptValid(char* code) {
    if(my_atoi(code, MAX_PIECES) != -1) {
        return 1;
    }
    return 0;
}


/**
 * Converts code as a string to be as an integer array
 * If any of the code characters are not a digit assigns -1
 * for that position.
*/
int* convertCArgToArray(char* str){
    static int code[CODE_SIZE] = {0, 0, 0 ,0};
    int* code_ptr = code;
    int index = 0;
    while(*str != '\0'){
        int value = (*str - 48);
        //check if valid number
        if(!(value >= 0 && value <= 7)){
            code[index] = -1;
        } else {
            code[index] = value;
        }
        str++;
        index++;
    }
    return code_ptr;
}

void checkFlagArguments(Board* board, Argument argument){
    if(argument.userSetAttempts == 1 && argument.previous[1] == 't') {
        int attempts = my_atoi(argument.current, MAX_SINGLE_DIGIT);
        //if failed to parce string to int value returns -1;
        if(attempts != -1){
            board->attempts = attempts;
        }
    }
    if(argument.userSetCode == 1 && argument.previous[1] == 'c') {
        int index;
        int* codeArray = convertCArgToArray(argument.current);
        if(isCFlagArgValid(codeArray)) {
            for(index = 0; index < CODE_SIZE; index++) {
                board->code[index] = codeArray[index];
            }
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
                    arg.userSetAttempts = 1;
                    break;
                case 'c' :
                    arg.userSetCode = 1;
                    break;
                default :
                    printf("[-%c] is an invalid option\n", arg.current[1]);
            }
        }
        arg.previous = argv[x - 1]; 
        checkFlagArguments(board, arg);        
    }  
}