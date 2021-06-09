#include "my_mastermind.h"


typedef struct Boards {
    int code[CODE_SIZE];
    int attempts;
} Board;

typedef struct Arguments {
    char* previous;
    char* current;
    int userSetCFlag;
    int userSetTFlag;
} Argument;

Board initBoardDefault();
int my_atoi(char* str);
void processArguments(Board* board,int argc, char* argv[]);
int isValidInput(void* code, int type);

int main(int argc, char* argv[]) {

    char input[CODE_SIZE];
    Board my_board = initBoardDefault();
    processArguments(&my_board, argc, argv);

    printf("Attempts you have:%d What is your guess?\n", my_board.attempts);
    read(STDIN_FILENO, input, sizeof(input));
    // int valid = isValidInput(input, 2);
    // printf("User validation: is input valid? %d\n", valid);



    return 0;


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
        int random_number = rand() % CODE_SIZE;
        board.code[x] = random_number;
    }
    board.attempts = 10;
    return board;

}
/**
 * str - a string that contains only digits
 *  
 *  returns positive integer conversion from string
 *  or returns -1 if string contains characters not a digit.
*/
int my_atoi(char* str) {
    int number = 0;
    int index = 0;
    while ((str[index] >= '0' && str[index] <= '9') || str[index] != '\0')
    {
        // multiply by base 10
        number *= 10;    
        // convet ASCII '0'..'9' to digit 0..9 and add it to number           
        number += str[index] - '0';
        // next character;         
        index++;                     
    }
    if (!(str[index] >= '0' && str[index] <= '9') || str[index] != '\0') {
        return -1;
    }
    return number;
}

int validateUserAttempt(int* arr){
    for(int x = 0; x < CODE_SIZE; x++){
        if(arr[x] == -1){
            return -1;
        }
    }
    return 0;
}

int isValidInput(void* code_ptr, int type){
    //1 char*
    //2 int*
    if(type == 1){
        char* code = (char*)code_ptr;
        if(my_atoi(code) != -1) {
            return 1;
        }
    }
    if(type == 2){
        int* code = (int*)code_ptr;
        if(validateUserAttempt(code) != -1){
            return -1;
        }
    }
    
    return 0;
}

int* convertStrToArray(char* str){
    static int code[CODE_SIZE] = {0, 0, 0 ,0};
    int* code_ptr = code;
    int index = 0;
    while(*str != '\0'){
        int value = (*str - 48);
        //check if valid number
        if(!(value >= 0 && value <= 9)){
            code[index] = -1;
        } else {
            code[index] = value;
        }
        str++;
        index++;
    }
    return code_ptr;
}

void checkFlagArguments(Board* board, Argument argument){
    int attempts = my_atoi(argument.current);
    if(argument.userSetTFlag == 1 && argument.previous[1] == 't') {
        //if failed to parce string to int value returns -1;
        if(attempts != -1){
            board->attempts = attempts;
        }
    }
    if(argument.userSetCFlag == 1 && argument.previous[1] == 'c') {
        int index;
        int* codeArray = convertStrToArray(argument.current);
        int valid = isValidInput(codeArray, 1);
        printf("Argument validation: -c valid? %d\n", valid);
        if(valid) {
            for(index = 0; index < CODE_SIZE; index++) {
                board->code[index] = codeArray[index];
                printf("%d\n", codeArray[index]);
            }
        }
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
                    arg.userSetTFlag = 1;
                    break;
                case 'c' :
                    arg.userSetCFlag = 1;
                    break;
                default :
                    printf("Invalid command\n" );
            }
        }
        arg.previous = argv[x - 1]; 
        checkFlagArguments(board, arg);        
    }  
}