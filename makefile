# the compiler: gcc for C program, define as g++ for C++
CC = gcc

# compiler flags:
#  	-g    adds debugging information to the executable file
#  	-Wall turns on most, but not all, compiler warnings
CFLAGS  = -g -Wall -Werror -Wextra

# the build target executable:
TARGET = kal

all: $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o build/$(TARGET)c $(TARGET).c

clean:
	$(RM) build/$(TARGET)