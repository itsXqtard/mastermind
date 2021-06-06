  # the compiler: gcc for C program
  CC = gcc

  # compiler flags:
  #  -g    adds debugging information to the executable file
  #  -Wall turns on most, but not all, compiler warnings
  #  -Wextra ??
  #  -Werror Make all warnings into errors.
  CFLAGS  = -g -Wall -Wextra -Werror

  # the build target executable:
  TARGET = my_mastermind

all: $(TARGET)

  $(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c

clean:
	rm $(TARGET)