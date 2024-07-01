#include "tcp_echo_client.h"

int tcp_echo_client_start(const char *ip, int port)
{
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd == -1)
    {
        perror("socket error");
        return -1;
    }
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;                 // ipv4
    server_addr.sin_port = htons(port);      // 端口号
    server_addr.sin_addr.s_addr = inet_addr(ip); // ip地址

    // connect
    if (connect(socket_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
    {
        perror("connect error");
        return -1;
    }
    char buf[128];
    printf(">>");
    while (fgets(buf , sizeof(buf), stdin))
    {
        if(send(socket_fd , buf, strlen(buf), 0) <= 0)
        {
            perror("send buf fail");
            return -1;
        }
        memset(buf , 0, sizeof(buf));

        size_t len = recv(socket_fd , buf, sizeof(buf) -1, 0);
        if(len <= 0)
        {
            perror("recv buf fail");
            return -1;
        }
        buf[len] = '\0';
        printf("recv:%s\n", buf);
        printf(">>");
    }
    close(socket_fd);
    return 0;
}