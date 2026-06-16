#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>

uint32_t hton32(uint32_t x)
{
    return htonl(x);
}

int main()
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);
    inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);

    connect(sock, (sockaddr*)&addr, sizeof(addr));

    printf("connected\n");

    const char* json = "{\"msg\":\"hello\"}";
    uint32_t len = strlen(json);
    uint32_t net_len = htonl(len);

    send(sock, &net_len, sizeof(net_len), 0);
    send(sock, json, len, 0);

    close(sock);
}
