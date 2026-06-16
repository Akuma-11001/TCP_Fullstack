// The main file for the gateway


#include "Server_Socket.h"
#include "Gateway.h"

#include <unistd.h>
#include <sys/socket.h>

#define PORT 8080

int main()
{
 



    int server_fd = create_server_socket(PORT);

    while (1)
    {
        int client_fd = accept(server_fd, NULL, NULL);
        handle_http_client(client_fd);
        close(client_fd);
    }

    return 0;

}
