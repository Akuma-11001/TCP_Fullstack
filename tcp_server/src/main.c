// This is the main file


#include <netinet/in.h>
#include <stdlib.h>
#include <time.h>

#include "Server.h"

   

#define PORT 8005
#define BUFFER_SIZE 1024


int main()
{
    srand((int)time(NULL));
    int server_fd = create_server_socket(PORT);

    run_server(server_fd);
   

    return 0;

}
