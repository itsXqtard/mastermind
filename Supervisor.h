#include "my_mastermind.h"
#ifndef SUPERVISOR
#define SUPERVISOR

/**
 * Checks if Supervisor mode is enabled
 * @param input    - A string that contains characters to enable supervisor mode (-a)
 * @return         - 0 or 1 for if user enabled supervisor mode
*/
int isSupervisorCommandEnabed(char input[]);
/**
 * Parce the user input to check and valid is supervisor mode is enabled. Checks whether
 * the size of the buffer is 3 for the two characters and a newline
 * @param input     - A string that contains characters to enable supervisor mode (-a)
 * @param size      - Size of the std in buffer. 
 * @return          - 0 or 1 for supervisor mode
*/
int processSupervisorMode(char input[], int size);
/**
 * Prints the answer for the board's code
 * @param board    - Information about the code
*/
void printCode(Board board);


#endif
