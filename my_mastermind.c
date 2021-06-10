#include "my_mastermind.h"


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
void processArguments(Board* board,int argc, char* argv[]);
int isUserAttemptValid(char* code);
void checkUserInput(Board* board, char* userAttempt);

int main(int argc, char* argv[]) {

    char input[CODE_SIZE];
    Board my_board = initBoardDefault();
    processArguments(&my_board, argc, argv);

    printf("Will you find the secret code?\n");
    int round = 0;
    do {
        printf("---\n");
        printf("Round %d\n", round);
        read(STDIN_FILENO, input, sizeof(input));
        int valid = isUserAttemptValid(input);
        if(valid == 0){
            printf("Wrong input!\n");
            continue;
        } else {
            write(STDOUT_FILENO, input, sizeof(input));
            checkUserInput(&my_board, input);
            my_board.attempts--;
            round++;
        }

    } while(my_board.attempts != 0);

    return 0;


}

char* findExactMatches(int boardCode[], char* userCode){
    static char exactMatches[CODE_SIZE] = {'x', 'x', 'x', 'x'};

    for(int x = 0; x < CODE_SIZE; x++) {
        if(boardCode[x] != (userCode[x] - '0')) {
            exactMatches[x] = userCode[x];
        }
    }
    return exactMatches;

}

void checkUserInput(Board* board, char* userAttempt) {
    char* matches = findExactMatches(board->code, userAttempt);
    // int exactCount = 0;
    printf("Matches {");
    for(int x = 0; x < CODE_SIZE; x++) {
        printf("%c", matches[x]);
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
    while ((str[index] >= '0' && str[index] <= max))
    {
        // multiply by base 10
        number *= 10;    
        // convet ASCII '0'..'9' to digit 0..9 and add it to number           
        number += str[index] - '0';
        // next character;         
        index++;                     
    }
    if(str[index] == '\0'){
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
int* convertStrToArray(char* str){
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
    int attempts = my_atoi(argument.current, MAX_SINGLE_DIGIT);
    if(argument.userSetTFlag == 1 && argument.previous[1] == 't') {
        //if failed to parce string to int value returns -1;
        if(attempts != -1){
            board->attempts = attempts;
        }
    }
    if(argument.userSetCFlag == 1 && argument.previous[1] == 'c') {
        int index;
        int* codeArray = convertStrToArray(argument.current);
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
                    arg.userSetTFlag = 1;
                    break;
                case 'c' :
                    arg.userSetCFlag = 1;
                    break;
                default :
                    printf("[-%c] is an invalid option\n", arg.current[1]);
            }
        }
        arg.previous = argv[x - 1]; 
        checkFlagArguments(board, arg);        
    }  
}