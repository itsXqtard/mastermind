#include "Arguments.h"


/**
 * Method that parces a string into an integer with specification of a max allowed to parce
 * @param str    - A string that contains only digits
 * @param limit  - Value that specifies the maximum parcer is allowed to parce
 * @return       - positive integer conversion from string
 *                 or returns -1 if string contains characters not a digit.
*/
static int my_atoi(char* str, int limit) {
    static int number = 0;
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
 * @param code  - Value inputted from the command line argument for c flag
 * @return      - 0 or 1 for valid command line input
 *
*/
static int isArgCodeValid(int* code) {
    for(int x = 0; x < CODE_SIZE; x++){
        if(code[x] == -1){
            return 0;
        }
    }
    return 1;
}

/**
 * Converts code as a string to be as an integer array
 * If any of the code characters are not a digit assigns -1
 * for that position.
 @param str     - string format for code of c flag
 @return        - pointer to place in memory to store int format of code
*/
static int* convertArgCodeToArray(char* str){
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

/**
 * Handles just the C Flag for code
 @param board     - contains information about game's board
 @param Argument  - contains information about flags that were passed into command line
*/
static void handleOptionCode(Board* board, Argument argument) {
    int* codeArray = convertArgCodeToArray(argument.current);
    if(isArgCodeValid(codeArray)) {
        for(int index = 0; index < CODE_SIZE; index++) {
            board->code[index] = codeArray[index];
        }
    }
}

/**
 * Handles just the T Flag for attempts
 @param board     - contains information about game's board
 @param Argument  - contains information about flags that were passed into command line
*/
static void handleOptionAttempt(Board* board, Argument argument) {
    int attempts = my_atoi(argument.current, MAX_SINGLE_DIGIT);
    //if failed to parce string to int value returns -1;
    if(attempts != -1){
        board->attempts = attempts;
    }
}

/**
 *  Checks the Flags from command line arguments and stores the values from the flags in board
 @param board     - contains information about game's board
 @param Argument  - contains information about flags that were passed into command line
*/
static void checkFlagArguments(Board* board, Argument argument) {
    if(argument.userSetAttempts == 1 && argument.previous[1] == 't') {
        handleOptionAttempt(board, argument);
    }
    if(argument.userSetCode == 1 && argument.previous[1] == 'c') {
        handleOptionCode(board, argument);
    }
}



/** 

NON STATIC METHODS 

**/



/**
 * Determines whether the value inputted by user is valid
 * checks if any of the character are digit values
 * @param code  - Value inputted from std input
 * @return      - 0 or 1 for valid input from user
**/
int isUserAttemptValid(char* code) {
    if(my_atoi(code, MAX_PIECES) != -1) {
        return 1;
    }
    return 0;
}
/**
 *  Iterates through the command line and parces and validates the command lines for different options
 @param board       - contains information about game's board
 @param argv        - contains all the arguments passed into the command line
*/
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