/*
 * using readn and writen
 * using readline
 * handle SIGPIPE
 */
#include "lnp_lt.h"

using namespace lt;

static void sigpipe_handler(int sig) {
    printf("receive sig=%d\n", sig);
}

int main(int argc, char* argv[]) {
    //signal(SIGPIPE, SIG_IGN);   // 一般情况下直接忽略就可以
    signal(SIGPIPE, sigpipe_handler);
    int clientfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (clientfd < 0)
        err::Exit("socket");

    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(5188);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(clientfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)
        err::Exit("connect");

    struct sockaddr_in localaddr;
    socklen_t addrlen = sizeof(localaddr);
    if (getsockname(clientfd, (struct sockaddr*)&localaddr, &addrlen) < 0)
        err::Exit("getsockname");

    printf("ip: %s, port: %d\n", inet_ntoa(localaddr.sin_addr), ntohs(localaddr.sin_port));

    char recvbuf[1024] = {0};
    char sendbuf[1024] = {0};
    while(fgets(sendbuf, sizeof(sendbuf), stdin) != NULL) {
        // write两次为了在server主动关闭后，先write一次收到RST段
        // 然后再write一次收到SIGPIPE信号
        writen(clientfd, sendbuf, 1);
        writen(clientfd, sendbuf + 1, strlen(sendbuf) - 1);
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

    close(clientfd);

    return 0;
}
