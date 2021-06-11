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

    char input[256];
    Board my_board = initBoardDefault();
    processArguments(&my_board, argc, argv);

    printf("Will you find the secret code with %d attempts\n", my_board.attempts);
    int round = 0;
    while(my_board.attempts != 0) {
        printf("---\n");
        printf("Round %d\n", round);
        int size = read(STDIN_FILENO, input, sizeof(input) + 1);
        if(!isUserAttemptValid(input) || size != 5){
            printf("Wrong input!\n");
        } else {
            printf("Valid Input: %c, %c, %c, %c\n", input[0],input[1],input[2],input[3]);
            checkUserInput(&my_board, input);
            my_board.attempts--;
            round++;
            printf("\n");
        }
    } 

    return 0;


}

/**
 * Returns count of exact positions
 * Side effect - Replaces non exact positions with user's input;
*/
int replaceAndReturnExactCount(int boardCode[], char* userCode, char matches[]){
    int exact = 0;
    for(int x = 0; x < CODE_SIZE; x++) {
        int userValue = userCode[x] - '0';
        if(userValue != boardCode[x]) {
            matches[x] = userCode[x];
            continue;
        }
        exact++;
    }
    return exact;
}

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

void checkUserInput(Board* board, char* userAttempt) {
    char exactMatches[CODE_SIZE + 1] = {'x', 'x', 'x', 'x', '\0'};
    int exact = replaceAndReturnExactCount(board->code, userAttempt, exactMatches);
    int totalMissplaced = CODE_SIZE - exact;
    int missplaced = 0;
    for(int x = 0; x < CODE_SIZE; x++) {
        if(exactMatches[x] == 'x'){
            continue;
        }
        if(contains(exactMatches, board->code[x]) == 1) {
            missplaced++;
        } 
    }
    totalMissplaced -= (totalMissplaced - missplaced);
    printf("exact: %d missplaced %d\n", exact, possibleMissplaced);
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
        //Multiply by base 10
        number *= 10;    
        // Convet current character to digit and add to current value.         
        number += str[index] - '0';
        // next character;         
        index++;                     
    }
    //check for '\n' key if taking input from stdin
    if(str[index] == '\n' || str[index] == '\0'){
        return number;
    }
    return -1;
}

/**
 *  Determines whether the value passed to the c flag in command line is valid
 *  checks if -1 is present in code
 *  Return 0 - not valid
 *  Return 1 - valid
 *
*/
int isArgCodeValid(int* code){
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
int* convertArgCodeToArray(char* str){
    static int code[CODE_SIZE] = {0, 0, 0 ,0};
    int* code_ptr = code;
    int index = 0;
    while(*str != '\0'){
        int value = (*str - '0');
        //check if valid number
        if(!(value >= 0 && value <= MAX_PIECES)){
            code[index] = -1;
        } else {
            code[index] = value;
        }
        str++;
        index++;
    }
    return code_ptr;
}

void handleOptionCode(Board* board, Argument argument){
    int* codeArray = convertArgCodeToArray(argument.current);
    if(isArgCodeValid(codeArray)) {
        for(int index = 0; index < CODE_SIZE; index++) {
            board->code[index] = codeArray[index];
        }
    }
}

void handleOptionAttempt(Board* board, Argument argument) {
    int attempts = my_atoi(argument.current, MAX_SINGLE_DIGIT);
    //if failed to parce string to int value returns -1;
    if(attempts != -1){
        board->attempts = attempts;
    }
}

void checkFlagArguments(Board* board, Argument argument){
    if(argument.userSetAttempts == 1 && argument.previous[1] == 't') {
        handleOptionAttempt(board, argument);
    }
    if(argument.userSetCode == 1 && argument.previous[1] == 'c') {
        handleOptionCode(board, argument);
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