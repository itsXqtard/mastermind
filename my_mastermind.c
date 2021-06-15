#include "my_mastermind.h"

int main(int argc, char* argv[]) {

    char input[256];
    Board my_board = initBoardDefault();
    processArguments(&my_board, argc, argv);

    printf("Will you find the secret code?\n");
    printf("You have %d attempts\n", my_board.attempts);
    int round = 0;
    while(my_board.attempts != 0) {
        printf("---\n");
        printf("Round %d\n", round);
        int size = read(STDIN_FILENO, input, sizeof(input) + 1);
        int secret = processSupervisorMode(input, size);
        if(secret == 1) {
            printCode(my_board);
            continue;
        }
        if(!isUserAttemptValid(input) || size != 5){
            printf("Wrong input!\n");
        } else {
            PlacedPiece placedpiece = checkUserInput(&my_board, input);
            if(placedpiece.wellPlaced == CODE_SIZE) {
                break;
            }
            printPlacedPieces(placedpiece);
            my_board.attempts--;
            round++;
        }
    }
    if(my_board.attempts == 0){
        printf("Better luck next time!\n"); 
    } else {
        printf("Congratz! You did it!\n"); 
    }
    

    return 0;
}