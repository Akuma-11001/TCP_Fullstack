
CC = gcc

CFLAGS = -Wall -Wextra -Wpedantic -g

SRC = main.cpp 
OUT = app

all:
	$(CC) $(CFLAGS) $(SRC) -o $(OUT)

run: all
	./$(OUT)

clean:
	rm -f $(OUT)

