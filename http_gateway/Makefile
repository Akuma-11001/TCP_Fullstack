CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -g 
CFLAGS += -Iinclude -I../Shared_Protocol

SRC = src/main.c src/Gateway.c\
	  ../Shared_Protocol/Protocol.c ../Shared_Protocol/Server_Socket.c 


OBJ = $(SRC:.c=.o)

TARGET = server

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	
