#include "my_mastermind.h"
#ifndef ARGUMENTS
#define ARGUMENTS

/**
 *
 * Container for holding information about the Arguments passed into command line
 *
**/
typedef struct Arguments {
    char* previous;
    char* current;
    int userSetCode;
    int userSetAttempts;
} Argument;

/**
 * Method that parces a string into an integer with specification of a max allowed to parce
 * @param str    - A string that contains only digits
 * @param limit  - Value that specifies the maximum parcer is allowed to parce
 * @return       - positive integer conversion from string
 *                 or returns -1 if string contains characters not a digit.
*/
int my_atoi(char* str, int limit);
/**
 *  Determines whether the value passed to the c flag in command line is valid
 *  checks if -1 is present in code
 * @param code  - Value inputted from the command line argument for c flag
 * @return      - 0 or 1 for valid command line input
 *
*/
int isArgCodeValid(int* code);
/**
 * Determines whether the value inputted by user is valid
 * checks if any of the character are digit values
 * @param code  - Value inputted from std input
 * @return      - 0 or 1 for valid input from user
**/
int isUserAttemptValid(char* code);
/**
 * Converts code as a string to be as an integer array
 * If any of the code characters are not a digit assigns -1
 * for that position.
 @param str     - string format for code of c flag
 @return        - pointer to place in memory to store int format of code
*/
int* convertArgCodeToArray(char* str);
/**
 * Handles just the C Flag for code
 @param board     - contains information about game's board
 @param Argument  - contains information about flags that were passed into command line
*/
void handleOptionCode(Board* board, Argument argument);
/**
 * Handles just the T Flag for attempts
 @param board     - contains information about game's board
 @param Argument  - contains information about flags that were passed into command line
*/
void handleOptionAttempt(Board* board, Argument argument);
/**
 *  Checks the Flags from command line arguments and stores the values from the flags in board
 @param board     - contains information about game's board
 @param Argument  - contains information about flags that were passed into command line
*/
void checkFlagArguments(Board* board, Argument argument);
/**
 *  Iterates through the command line and parces and validates the command lines for different options
 @param board       - contains information about game's board
 @param argv        - contains all the arguments passed into the command line
*/
void processArguments(Board* board, int argc, char* argv[]);

#endif