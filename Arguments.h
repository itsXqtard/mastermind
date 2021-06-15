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


int isUserAttemptValid(char* code);
void processArguments(Board* board, int argc, char* argv[]);

#endif