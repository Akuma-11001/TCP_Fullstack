// This is the main file


#include <netinet/in.h>

#include "Server.h"

   

#define PORT 8081
#define BUFFER_SIZE 1024


int main()
{

    int server_fd = create_server_socket(PORT);

    run_server(server_fd);
   

    return 0;

}
