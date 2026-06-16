// The definitions for the Gateway are here




#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#include "Protocol.h"

#define HTTP_PORT 8080
#define TCP_PORT  8081
#define TCP_IP    "127.0.0.1"

int tcp_call(const char *request_json, char **response_json)
{
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0)
    {
        perror("socket");
        return -1;
    }

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));

    addr.sin_family = AF_INET;
    addr.sin_port = htons(TCP_PORT);
    inet_pton(AF_INET, TCP_IP, &addr.sin_addr);

    if (connect(fd, (struct sockaddr*)&addr, sizeof(addr)) < 0)
    {
        perror("connect");
        close(fd);
        return -1;
    }

    if (send_packet(fd, request_json) < 0)
    {
        perror("send_packet");
        close(fd);
        return -1;
    }

    int len = receive_packet(fd, response_json);

    close(fd);

    return len;
}


void send_http_response(int client_fd, const char *json_body)
{
    char buffer[4096];

    snprintf(buffer, sizeof(buffer),
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

void serve_file(int client_fd, const char *path)
{



    FILE *file = fopen(path, "r");
    printf("Opening: %s\n", path);

    if (!file)
    {
        const char *not_found =
            "HTTP/1.1 404 Not Found\r\n"
            "Content-Type: text/plain\r\n"
            "\r\n"
            "404";

        send(client_fd, not_found, strlen(not_found), 0);
        return;
    }

    char buffer[4096];
    size_t n;

    char response_header[512];
    snprintf(response_header, sizeof(response_header),
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html\r\n"
        "\r\n");

    send(client_fd, response_header, strlen(response_header), 0);

    while ((n = fread(buffer, 1, sizeof(buffer), file)) > 0)
    {
        send(client_fd, buffer, n, 0);
    }

    fclose(file);
}

void handle_http_client(int client_fd)
{
    char buffer[4096];

    int bytes = read(client_fd, buffer, sizeof(buffer) - 1);
    if (bytes <= 0)
        return;

    buffer[bytes] = '\0';

    if (strncmp(buffer, "GET / HTTP/1.1", 14) == 0)
    {
        serve_file(client_fd, "frontend/index.html");
        return;
    }


    if (strstr(buffer, "GET /favicon.ico"))
    {
        serve_file(client_fd, "frontend/favicon.ico");
        return;
    }   

    printf("REQUEST BUFFER: \n%s\n", buffer);

    // Find HTTP body (very simple parsing)
    char *body = strstr(buffer, "\r\n\r\n");
    if (body)
    {

        body += 4; // skip header separator

        printf("HTTP Body: %s\n", body);

        char *tcp_response = NULL;

        if (tcp_call(body, &tcp_response) < 0)
        {
            const char *err = "{\"error\":\"tcp failed\"}";
            send_http_response(client_fd, err);
            return;
        }

        send_http_response(client_fd, tcp_response);

        free(tcp_response);
    }
}
