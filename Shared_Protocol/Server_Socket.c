// The server_socket definition file



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/socket.h>
#include <netinet/in.h>

#define BUFFER_SIZE 1024



int create_server_socket(int PORT)
{
    




    int server_fd;
    struct sockaddr_in address;


    // Create Socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0); // The arguments are: domain (IPv4), SOCK_STREAM
                                                 //     and Protocol (here its TCP) 
    if (server_fd < 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Configure address
    memset(&address, 0, sizeof(address));   // Buffer becomes 0 [0][0]...
    address.sin_family = AF_INET;           // IPv4
    address.sin_addr.s_addr = INADDR_ANY;   // This means that i want ANY network interface
    address.sin_port = htons(PORT);         // Dont fully understand this one, but it converts port 
                                        //      into network byte order, because of endians
                                        //      htons = host to network short

    // Bind
    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0)
    {                                   // I am using the address struct to have the information 
                                        //      to attach these to the socket 
                                        //      Example: 0.0.0.0:8080
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // Listen
    if (listen(server_fd, 5) < 0)       // Start listening for connections as the server
                                        // (5 here means log the client wait queue. So clients 
                                        // that have done the TCP handshake, but havent 
                                        // been accepted yet by the program)
    {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", PORT);

    return server_fd;
}

