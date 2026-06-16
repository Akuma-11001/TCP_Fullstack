// The Client data is being handled here

#include "Client.h"
#include "Protocol.h"

#include <stdio.h>
//#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include <sys/socket.h>
#include <netinet/in.h>

#define BUFFER_SIZE 1024






// This is the next version of the code
//
//void handle_client(int client_fd)
//{
//    while (1)
//    {
//        char * packet;
//
//        int result = receive_packet(client_fd, &packet);
//
//        if (result <=0)
//        {
//            break;
//        }
//
//        printf("JSON: %s\n", packet);
//
//        send_packet(client_fd, "{\"status\":\"ok\"}");
//        
//        free(packet);
//
//    }
//}
//
//
//
// This was the code before, when I didnt use JSON 

//void handle_client2(int client_fd)
//{
//    char buffer[BUFFER_SIZE];
//    // Read data
//    int bytes = read(client_fd, buffer, BUFFER_SIZE - 1);
//    while (bytes > 0)
//    {
//        printf("Received: %s\n", buffer);
//                                // So clear the buffer memory to 0 bytes in the 
//                                // if statement, so it only clears when needed
//        buffer[bytes] = '\0';   // has to be '', because of characters 
//                                // "" does have a terminating null byte added (only for array of chars)
//    }                           // only does [0] for the bytes size  
//    if (bytes == 0)
//    {
//        printf("Client disconnected\n");
//        
//    }
//    else if  (bytes < 0)
//    {
//        perror("read failed");
//        
//    }
//
//    // Send a response
//    const char* response = "Hello from the TCP-Server\n";
//    send(client_fd, response, strlen(response), 0);   
//
//    
//}
//
//
