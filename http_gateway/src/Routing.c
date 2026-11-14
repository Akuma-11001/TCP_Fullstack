// The definitions of the routing functions


#include "Routing.h"
#include "Gateway.h"

#include <stdio.h>


#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <arpa/inet.h>

Route routes[] =
{
    {"GET", "/", handle_index},
    {"GET", "/styles.css", handle_css},
    {"GET", "/favicon.ico", handle_favicon},
    {"GET", "/login", handle_login_page},
    {"POST", "/login", handle_login},
};


void send_404(int client_fd)
{
    const char *response =
        "HTTP/1.1 404 Not Found\r\n"
        "Content-Type: text/html\r\n"
        "Connection: close\r\n"
        "\r\n"
        "<!DOCTYPE html>"
        "<html>"
        "<head><title>404 Not Found</title></head>"
        "<body>"
        "<h1>404 - Page Not Found</h1>"
        "<p>The requested resource could not be found.</p>"
        "</body>"
        "</html>";

    send(client_fd, response, strlen(response), 0);
}

void serve_file(int client_fd, const char *path, const char *content_type)
{
    // This is to serve html pages


    FILE *file = fopen(path, "r");
    printf("Opening: %s\n", path); // To Debug what file is getting opened
                                   // Should probably add the file into the print

    if (!file)  // Check if the file is available
    {
        const char *not_found =
            "HTTP/1.1 404 Not Found\r\n"
            "Content-Type: %s\r\n"
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
        "Content-Type: %s\r\n"
        "Connection: close\r\n"
        "\r\n", content_type);

    send(client_fd, response_header, strlen(response_header), 0);

    while ((n = fread(buffer, 1, sizeof(buffer), file)) > 0) // So the file is being
        // constantly shown. This only sends some data every loop, until it sent   
        // the complete file data
    {
        send(client_fd, buffer, n, 0);
    }

    fclose(file);
}







void handle_index(int client_fd, const char *request)
{
    char *tcp_response = NULL;
    if (tcp_call("visualize", &tcp_response)< 0)
    {
        printf("TCP communication failed\n");
    }
    else
    {
        printf("TCP response: %s\n", tcp_response);

        free(tcp_response);
    }


    serve_file(client_fd, "frontend/index.html","text/html");
}




void handle_css(int client_fd, const char *request)
{
   serve_file(client_fd, "frontend/Layout.css", "text/css");
}







void handle_favicon(int client_fd, const char *request)
{
    serve_file(client_fd, "frontend/favicon.ico", "image/x-icon");
}


void handle_login_page(int client_fd, const char *request)
{
   // serve_file(client_fd, "frontend/index.html");
}


void handle_login(int client_fd, const char *request)
{
   // serve_file(client_fd, "frontend/index.html");
}




void parse_request(const char *request, char *method, char *path)
{
    sscanf(request, "%s %s", method, path);
}



void route_request(int client_fd, const char *request)
{

    char method[8];
    char path[256];
    parse_request(request, method, path);


    int route_count = sizeof(routes) / sizeof(routes[0]);

    for (int i=0; i < route_count ; i++)
    {
        if (strcmp(routes[i].method, method) == 0 &&
            strcmp(routes[i].path, path) == 0)
        {
            routes[i].handler(client_fd, request);
            return;
        }
    }
    send_404(client_fd);
}
