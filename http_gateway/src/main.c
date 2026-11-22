// The main file for the gateway


#include "Server_Socket.h"
#include "Gateway.h"
#include "Routing.h"

#include <unistd.h>
#include <sys/socket.h>

#define PORT 9000

int main()
{
 



    int server_fd = create_server_socket(PORT);

    while (1)
    {
        int client_fd = accept(server_fd, NULL, NULL);
        handle_http_client(client_fd); 

        
        close(client_fd);
        
    }
    close(server_fd); // This is needed, because if not, the server 
                      // does not shutdown correctly, when you load an html page
                      // in the browser

                      // I had the error when stoping the server and starting it again
    return 0;

}
