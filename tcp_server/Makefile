
CC = gcc

CFLAGS = -Wall -Wextra -Wpedantic -g

INCLUDE = include/Client.hpp include/Server.hpp ../Shared_Protocol/Protocol.hpp \
		  ../Shared_Protocol/Server_Socket.hpp

SRC = src/main.cpp src/Client.cpp src/Server.cpp ../Shared_Protocol/Protocol.cpp \
	  ../Shared_Protocol/Server_Socket.cpp
OUT = app

all:
	$(CC) $(CFLAGS) $(SRC) -o $(OUT)

run: all
	./$(OUT)

clean:
	rm -f $(OUT)


