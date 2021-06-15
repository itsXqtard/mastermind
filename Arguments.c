#include "Arguments.h"


int my_atoi(char* str, int limit) {
    int number = 0;
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



int isArgCodeValid(int* code){
    for(int x = 0; x < CODE_SIZE; x++){
        if(code[x] == -1){
            return 0;
        }
    }
    return 1;
}


int isUserAttemptValid(char* code) {
    if(my_atoi(code, MAX_PIECES) != -1) {
        return 1;
    }
    return 0;
}



int* convertArgCodeToArray(char* str){
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

void handleOptionCode(Board* board, Argument argument){
    int* codeArray = convertArgCodeToArray(argument.current);
    if(isArgCodeValid(codeArray)) {
        for(int index = 0; index < CODE_SIZE; index++) {
            board->code[index] = codeArray[index];
        }
    }
}

void handleOptionAttempt(Board* board, Argument argument) {
    int attempts = my_atoi(argument.current, MAX_SINGLE_DIGIT);
    //if failed to parce string to int value returns -1;
    if(attempts != -1){
        board->attempts = attempts;
    }
}

void checkFlagArguments(Board* board, Argument argument){
    if(argument.userSetAttempts == 1 && argument.previous[1] == 't') {
        handleOptionAttempt(board, argument);
    }
    if(argument.userSetCode == 1 && argument.previous[1] == 'c') {
        handleOptionCode(board, argument);
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