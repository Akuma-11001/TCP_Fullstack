// The declaration functions for the Routing


#pragma once

typedef struct
{
    const char *method;
    const char *path;
    void (*handler)(int client_fd, const char *request);
} Route;


void serve_file(int client_fd, const char *path, const char *content_type);

void parse_request(const char *request, char *method, char *path);

void route_request(int client_fd, const char *request);






void send_404(int client_fd);

void handle_index(int client_fd, const char *request);


void handle_css(int client_fd, const char *request);

void handle_fetching(int client_fd, const char *request);

void handle_visualization(int client_fd, const char *request);

void handle_favicon(int client_fd, const char *request);

void handle_login_page(int client_fd, const char *request);

void handle_login(int client_fd, const char *request);

