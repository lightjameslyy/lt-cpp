/*
 * using readn and writen
 * using readline
 * create 5 clients, the first client works
 */
#include "lnp_lt.h"

using namespace lt;

static void echo_client(int clientfd) {
    char recvbuf[1024] = {0};
    char sendbuf[1024] = {0};
    while(fgets(sendbuf, sizeof(sendbuf), stdin) != NULL) {
        writen(clientfd, sendbuf, strlen(sendbuf)); // fgets获取的数据默认带'\n'
        int ret = readline(clientfd, recvbuf, sizeof(recvbuf));
        if (ret == -1)
            err::Exit("readline");
        if (ret == 0) {
            printf("server close\n");
            break;
        }
        fputs(recvbuf, stdout);
        memset(recvbuf, 0, sizeof(recvbuf));
        memset(sendbuf, 0, sizeof(sendbuf));
    }
}

int main(int argc, char* argv[]) {
    int clientfd[5];
    for (int i = 0; i < 5; ++i) {
        if ((clientfd[i] = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
            err::Exit("socket");

        struct sockaddr_in servaddr;
        memset(&servaddr, 0, sizeof(servaddr));
        servaddr.sin_family = AF_INET;
        servaddr.sin_port = htons(5188);
        servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

        if (connect(clientfd[i], (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)
            err::Exit("connect");

        struct sockaddr_in localaddr;
        socklen_t addrlen = sizeof(localaddr);
        if (getsockname(clientfd[i], (struct sockaddr*)&localaddr, &addrlen) < 0)
            err::Exit("getsockname");

        printf("ip: %s, port: %d\n", inet_ntoa(localaddr.sin_addr), ntohs(localaddr.sin_port));
    }

    echo_client(clientfd[0]);

    for (int i = 0; i < 5; ++i)
        close(clientfd[i]);

    return 0;
}
