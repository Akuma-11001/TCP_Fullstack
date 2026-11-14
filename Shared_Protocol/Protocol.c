// The protocol file for JSON parsing



#include "Protocol.h"

// So low-level data (uints)
// normal logic and calculations (int, float, long, ...)
// Text, Byte streams, raw memory buffers (char)



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/socket.h>
#include <arpa/inet.h>






static void log_bytes(const char *direction, const char *data, size_t length)
{
    printf("[%s] %zu bytes", direction, length);

    for (size_t i = 0; i < length; i++)
    {
        printf("%02X", data[i]);
    }
    printf("\n");
    fflush(stdout);
}


static int read_exact(int fd, void *buffer, size_t bytes_to_read)
{
    size_t total = 0;

    printf("read_exact called");

    while (total < bytes_to_read)
    {
        int bytes = read(
                fd,
                (char*)buffer + total,
                bytes_to_read - total
            );

        if (bytes <= 0)
            return -1;

        log_bytes("RX", (char*)buffer + total, bytes);

        total += bytes;
    }

    return total;
}

static int send_exact(int fd, const  void *buffer, size_t bytes_to_read)
{
    size_t total = 0;

    printf("send_exact called");

    while (total < bytes_to_read)
    {
        int bytes = send(
                fd,
                (const char*)buffer + total,
                bytes_to_read - total, 0
            );

        if (bytes <= 0)
            return -1;




        log_bytes("TX", (char*)buffer + total, bytes);

        total += bytes;
    }

    return total;
}




int receive_packet(int client_fd, char **out_buffer)
{
    uint32_t net_length; // Is a buffer



    if (read_exact(client_fd, &net_length, sizeof(net_length)) < 0)
    {
        return -1;
    }


    uint32_t payload_length = ntohl(net_length);

    if (payload_length > 1024 * 1024)
        return -1;
    
    

    char *payload = (char*)malloc(payload_length + 1);


    if (!payload)
        return -1;

    if (read_exact(client_fd, payload, payload_length) < 0)
    {
        free(payload);
        return -1;
    }

    payload[payload_length] = '\0';  // So clear the  memory to 0 bytes 
                                    // has to be '', because of characters 
                                    // "" does have a terminating null byte added 
                                    // (only for array of chars), '0' this only fills the first one
                                   


    *out_buffer = payload;


    return payload_length;


}


int send_packet(int client_fd, const char *json)
{
    uint32_t payload_length = strlen(json);


    uint32_t net_length = htonl(payload_length);


    if (send_exact(client_fd,
                &net_length,
                sizeof(net_length)
                ) < 0)

        return -1;

    if (send_exact(client_fd,
                json,
                payload_length
                ) < 0)

        return -1;

    return 0;
}
