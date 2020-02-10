/*
 * using readn and writen
 * using readline
 * handle SIGPIPE
 * using select manage stdin I/O and socket I/O
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
    close(clientfd);
}


static void echo_client_select(int sock) {
    fd_set readSet;
    FD_ZERO(&readSet);

    int fd_stdin = fileno(stdin);
    int maxfd = (fd_stdin > sock ? fd_stdin : sock);
    char recvbuf[1024] = {0};
    char sendbuf[1024] = {0};
    while(1) {
        FD_SET(fd_stdin, &readSet);
        FD_SET(sock, &readSet);
        int nReady = select(maxfd + 1, &readSet, NULL, NULL, NULL);
        if (nReady == -1)
            err::Exit("select");
        if (nReady == 0)    // 超时
            continue;

        if (FD_ISSET(sock, &readSet)) {
            int ret = readline(sock, recvbuf, sizeof(recvbuf));
            if (ret == -1)
                err::Exit("readline");
            if (ret == 0) {
                printf("server close\n");
                break;
            }
            fputs(recvbuf, stdout);
            memset(recvbuf, 0, sizeof(recvbuf));
        }

        if (FD_ISSET(fd_stdin, &readSet)) {
            if (fgets(sendbuf, sizeof(sendbuf), stdin) == NULL) // EOF
                break;
            writen(sock, sendbuf, strlen(sendbuf)); // fgets获取的数据默认带'\n'
            //memset(sendbuf, 0, sizeof(sendbuf));
        }
    }
    close(sock);
}

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

    //echo_client(clientfd);
    echo_client_select(clientfd);

    return 0;
}
