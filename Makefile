  # the compiler: gcc for C program
  CC = gcc

  # compiler flags:
  #  -g    adds debugging information to the executable file
  #  -Wall turns on most, but not all, compiler warnings
  #  -Wextra - errors on unused variables
  #  -Werror Make all warnings into errors.
  CFLAGS  = -g -Wall -Wextra -Werror
  # the build target executable:
  TARGET = my_mastermind

all: $(TARGET) 

$(TARGET): my_mastermind.o Board.o Arguments.o Supervisor.o
	$(CC) $(CFLAGS) $(TARGET).o Board.o Arguments.o Supervisor.o -o $(TARGET)


my_mastermind.o: my_mastermind.c
	$(CC) $(CFLAGS) -c my_mastermind.c
Arguments.o: Arguments.c
	$(CC) $(CFLAGS) -c Arguments.c
Board.o: Board.c
	$(CC) $(CFLAGS) -c Board.c
Supervisor.o: Supervisor.c
	$(CC) $(CFLAGS) -c Supervisor.c



clean:
	rm $(TARGET) *.o