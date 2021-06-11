#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define CODE_SIZE 4
#define MAX_PIECES 7
#define MAX_SINGLE_DIGIT 9
#define EXACT 'x'
#define MISPLACED 'm'
#define EMPTY '-'

enum t_typename {
    TYPENAME_BOOL,
    TYPENAME_UNSIGNED_CHAR,
    TYPENAME_CHAR,
    TYPENAME_SIGNED_CHAR,
    TYPENAME_SHORT_INT,
    TYPENAME_UNSIGNED_CHORT_INT,
    TYPENAME_INT,
    TYPENAME_UNSIGNED_LONG_INT,
    TYPENAME_UNSIGNED_LONG_LONG_INT,
    TYPENAME_LONG_INT,
    TYPENAME_LONG_LONG_INT,
    TYPENAME_POINTER_TO_CHAR,
    TYPENAME_FLOAT,
    TYPENAME_DOUBLE,
    TYPENAME_DOUBLE_FLOAT,
    TYPENAME_POINTER_TO_INT,
    TYPENAME_POINTER_TO_VOID,
    TYPENAME_OTHER
};
    
    #define typename(x) _Generic((x),                                                       \
            _Bool: TYPENAME_BOOL,           unsigned char: TYPENAME_UNSIGNED_CHAR,          \
             char: TYPENAME_CHAR,             signed char: TYPENAME_SIGNED_CHAR,            \
        short int: TYPENAME_SHORT_INT, unsigned short int: TYPENAME_UNSIGNED_SHORT_INT,     \
              int: TYPENAME_INT,                   double: TYPENAME_UNSIGNED_INT,                 \
         long int: TYPENAME_LONG_INT,   unsigned long int: TYPENAME_UNSIGNED_LONG_INT,      \
    long long int: TYPENAME_LONG_LONG_INT, unsigned long long int: TYPENAME_UNSIGNED_LONG_LONG_INT, \
            float: TYPENAME_FLOAT,                         double: TYPENAME_DOUBLE,                 \
      long double: TYPENAME_DOUBLE_FLOAT,                   char *: TYPENAME_POINTER_TO_CHAR,        \
           void *: TYPENAME_POINTER_TO_VOID,                int *: TYPENAME_POINTER_TO_INT,         \
          default: TYPENAME_OTHER)
