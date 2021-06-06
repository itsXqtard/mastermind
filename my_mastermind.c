#include <stdio.h>
#include <stdlib.h>
#include<time.h>

#define CODE_SIZE 4

typedef struct Boards {
    int code[CODE_SIZE];
    int attempts;
} Board;

struct Arguments {
    char* cFlag;
    int tFlag;
};

Board initBoardDefault();
Arguments processArguments(int argc, char* argv[]);

int main(int argc, char* argv[]) {

    printf("%d %s\n", argc, argv[0]);

    Board my_board = initBoardDefault();
    struct Arguments args = {0, 0};

    printf("Attempts:%d, cFlag: %d tFlag: %d\n", my_board.attempts, args.cFlag, args.tFlag);

    return 0;


}

Board initBoardDefault() {
    Board board = {};

    //seed the randome generator with current time;
    srand(time(0));
    for(int x = 0; x < CODE_SIZE; x++){
        int random_number = rand() % 4;
        board.code[x] = random_number;
    }
    board.attempts = 10;
    return board;

}

Arguments processArguments(int argc, char* argv[]) {
    struct Arguments argument = {"", 0}
    
}