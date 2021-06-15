#include "Supervisor.h"

int isSupervisorCommandEnabed(char input[]) {
    if(input[0] == '-' && input[1] == 's'){
        return 1;
    }
    return 0;
}

void printCode(Board board) {
    printf("Answer: ");
    for(int x = 0; x < CODE_SIZE; x++){
        printf("%d", board.code[x]);
    }
    printf("\n");
}

int processSupervisorMode(char input[], int size) {
    int secret = 0;
    if(size == 3) {
        if(isSupervisorCommandEnabed(input)) {
            secret = 1;
        }
    }
    return secret;
}