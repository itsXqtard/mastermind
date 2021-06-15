#include "Supervisor.h"

/**
 * Checks if Supervisor mode is enabled
 * @param input    - A string that contains characters to enable supervisor mode (-a)
 * @return         - 0 or 1 for if user enabled supervisor mode
*/
static int isSupervisorCommandEnabed(char input[]) {
    if(input[0] == '-' && input[1] == 's'){
        return 1;
    }
    return 0;
}

/** 

NON STATIC METHODS 

**/


/**
 * Prints the answer for the board's code
 * @param board    - Information about the code
*/
void printCode(Board board) {
    printf("Answer: ");
    for(int x = 0; x < CODE_SIZE; x++){
        printf("%d", board.code[x]);
    }
    printf("\n");
}

/**
 * Parce the user input to check and valid is supervisor mode is enabled. Checks whether
 * the size of the buffer is 3 for the two characters and a newline
 * @param input     - A string that contains characters to enable supervisor mode (-a)
 * @param size      - Size of the std in buffer. 
 * @return          - 0 or 1 for supervisor mode
*/
int processSupervisorMode(char input[], int size) {
    int secret = 0;
    if(size == 3) {
        if(isSupervisorCommandEnabed(input)) {
            secret = 1;
        }
    }
    return secret;
}