// The server logic is inside this file





#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/socket.h>
#include <netinet/in.h>

#include "../include/Server.hpp"
#include "../include/Client.hpp"
#include "../../Shared_Protocol/Protocol.hpp"

#define PORT 8080
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

    
    const char *response = "{\"ok\": true}";

    send_packet(client_fd, response);

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
        if (client_fd < 0)                  // Now this is the client that becomes the connection
        {                                   //  The client is also made with the from
                                            //  from the server (Domain, Socket_Stream, Protocol) 
            perror("accept failed");        // Serve and Client both have a socket
            continue;
        }
        handle_client(client_fd);
        close(client_fd);
    } 
}


//
