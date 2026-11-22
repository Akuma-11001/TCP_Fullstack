// The definitions for the Gateway are here




#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>



#include <netdb.h>

#include "Protocol.h"
#include "Routing.h"


#define HTTP_PORT 9000
#define TCP_PORT  8005








static int create_tcp_server()
{
   
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0) // Make a socket
    {
        perror("socket");
        return -1;
    }

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));

    addr.sin_family = AF_INET;
    addr.sin_port = htons(TCP_PORT);

    const char *host = getenv("TCP_SERVER_HOST");

    if (host == NULL)
        host = "127.0.0.1";

    struct hostent *server = gethostbyname(host);

    if (server == NULL)
    {
        fprintf(stderr, "Could not resolve TCP server: %s\n", host);
        close(fd);
        return -1;
    }

    memcpy(&addr.sin_addr, server->h_addr_list[0], server->h_length);




// Connect the socket with using the addr struct to get the TCP Server
    if (connect(fd, (struct sockaddr*)&addr, sizeof(addr)) < 0) 
    {
        perror("connect");
        close(fd);
        return -1;
    }

    return fd;
}

int tcp_call(const char *request_json, char **response_json)
{
    int fd = create_tcp_server();

    if (fd < 0) 
    {
        fprintf(stderr, "Could not connect to the TCP server \n");
        return -1;
    }

 if (send_packet(fd, request_json) < 0) // Send the packet to the tcp server
    {
        perror("send_packet");
        close(fd);
        return -1;
    }

    int len = receive_packet(fd, response_json); // save the length of the packet 
    // from the TCP Server
    if (len < 0)
    {
        printf("TCP receive failed\n");
        close(fd);
        return -1;
    }

    close(fd);

    return len;
}


void send_http_response(int client_fd, const char *json_body) // Gets send to the browser
{
    char buffer[4096];

    snprintf(buffer, sizeof(buffer),  // I guess its to add the text to the buffer
                                      // The snprintf does make text into a string, so
                                      // it doesnt print

        "HTTP/1.1 200 OK\r\n"
        "Content-Type: application/json\r\n"
        "Content-Length: %zu\r\n"
        "Connection: close\r\n"
        "\r\n"
        "%s",
        strlen(json_body),
        json_body
    );

    send(client_fd, buffer, strlen(buffer), 0);
}


int handle_http_client(int client_fd) // This uses the serve_file function
                                       // to send data, which includes the html page
                                       // to the browser
    // Better explanation:
    // Handle a single HTTP request from the browser.
    // Serve static files or forward API requests to the TCP server.
{
    char buffer[4096];

    int bytes = read(client_fd, buffer, sizeof(buffer) - 1);
    if (bytes <= 0)
        return -1;

    buffer[bytes] = '\0';



    printf("REQUEST BUFFER: \n%s\n", buffer);
            
    route_request(client_fd, buffer);

    return 0;
}

