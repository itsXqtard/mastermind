#include "my_mastermind.h"
#ifndef SUPERVISOR
#define SUPERVISOR

int isSupervisorCommandEnabed(char input[]);
void printCode(Board board);
int processSupervisorMode(char input[], int size);

#endif
