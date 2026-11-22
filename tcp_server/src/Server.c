// The server logic is inside this file





#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/socket.h>
#include <netinet/in.h>

#include "Server.h"
#include "Client.h"
#include "Protocol.h"

#define BUFFER_SIZE 1024




void handle_client(int client_fd)
{
    char *request = NULL;

    if (receive_packet(client_fd, &request) < 0)
    {
        perror("receive failed");
        return;
    }

    printf("Received: %s\n", request);

    



    
    if (strcmp(request, "visualization")==0)
    {
        char response[512];
        char hex[400] = "";

        for (int i = 0; i < 32; i++)
        {
            char byte[4];
            snprintf(byte, sizeof(byte), "%02X", rand() % 256);
            strcat(hex, byte);
        }
    

        snprintf(response, sizeof(response), "{\"hex\": \"%s\"}", hex);
    
        send_packet(client_fd, response);
    }
    free(request);
}

int accept_client(int server_fd)
{
    struct sockaddr_in client_addr;
    socklen_t addrlen = sizeof(client_addr);

    int client_fd = accept(server_fd,
                            (struct sockaddr*)&client_addr,
                            &addrlen);

    if (client_fd < 0)
    {
        perror("accept failed");
        return -1;
    }

    return client_fd;
}


void run_server(int server_fd)
{
    while (1)
    {
        int client_fd = accept_client(server_fd);
// Accepts the connections
// Now this is the client that becomes the connection
// The client is also made 
//      from the server (Domain, Socket_Stream, Protocol) 
// Server and Client both have a socket

        if (client_fd < 0)                 
        {
            perror("accept failed");                    
            continue;
        }
        handle_client(client_fd);
        close(client_fd);
    } 
}


//
