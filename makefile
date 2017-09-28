# the compiler: gcc for C program, define as g++ for C++
CC = gcc

# compiler flags:
#  	-g    adds debugging information to the executable file
#  	-Wall turns on most, but not all, compiler warnings
CFLAGS  = -g -Wall -Werror -Wextra

# the build target executable:
TARGETS = scanner.c kal.c
OUTFILE = kalc

all: $(OUTFILE)

$(OUTFILE): $(TARGETS)
	$(CC) $(CFLAGS) $(TARGETS) -o build/$(OUTFILE)

clean:
	$(RM) build/$(OUTFILE)