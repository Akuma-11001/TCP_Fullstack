// The Server declaration file


#pragma once

int create_server_socket();
int accept_client(int server_fd);
void handle_client(int client_fd);


void run_server(int sever_fd);

