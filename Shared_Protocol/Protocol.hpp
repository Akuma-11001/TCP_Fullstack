// The protocol for JSON parsing


#pragma once


#include <stdint.h>

int receive_packet(int client_fd, char** out_buffer);
int send_packet(int client_fd, const char* json);
