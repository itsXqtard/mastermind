#include "my_mastermind.h"
#ifndef ARGUMENTS
#define ARGUMENTS


typedef struct Arguments {
    char* previous;
    char* current;
    int userSetCode;
    int userSetAttempts;
} Argument;

/**
 * str - a string that contains only digits between 0-limit
 *  
 *  returns positive integer conversion from string
 *  or returns -1 if string contains characters not a digit.
*/
int my_atoi(char* str, int limit);
/**
 *  Determines whether the value passed to the c flag in command line is valid
 *  checks if -1 is present in code
 *  Return 0 - not valid
 *  Return 1 - valid
 *
*/
int isArgCodeValid(int* code);
/**
 * Determines whether the value inputted by user is valid
 * checks if any of the character are digit values
 * Return 0 - not valid
 * Return 1 - valid
*/
int isUserAttemptValid(char* code);
/**
 * Converts code as a string to be as an integer array
 * If any of the code characters are not a digit assigns -1
 * for that position.
*/
int* convertArgCodeToArray(char* str);
void handleOptionCode(Board* board, Argument argument);
void handleOptionAttempt(Board* board, Argument argument);
void checkFlagArguments(Board* board, Argument argument);
void processArguments(Board* board, int argc, char* argv[]);

#endif