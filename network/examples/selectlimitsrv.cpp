/*
 * test select limit
 */

#include "lnp_lt.h"

using namespace lt;

int main(int argc, char* argv[]) {
    int listenfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (listenfd < 0)
        err::Exit("socket");

    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(5188);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);   // 0.0.0.0, for server
    //servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    //inet_aton("127.0.0.1", &servaddr.sin_addr);

    int on = 1;
    if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0)
        err::Exit("setsockopt");

    if (bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)
        err::Exit("bind");

    if (listen(listenfd, SOMAXCONN) < 0)
        err::Exit("listen");

    struct sockaddr_in peeraddr;
    socklen_t peerlen = sizeof(peeraddr);
    int connfd;

    int count = 0;
    int maxclient = 0;
    int client[FD_SETSIZE];
    for (int i = 0 ; i < FD_SETSIZE; ++i)
        client[i] = -1; // 用-1表示空闲

    fd_set readSet;
    fd_set allSet;
    FD_ZERO(&readSet);
    FD_ZERO(&allSet);
    FD_SET(listenfd, &allSet);
    int maxfd = listenfd;
    while (1) {
        readSet = allSet;
        int nReady = select(maxfd + 1, &readSet, NULL, NULL, NULL);
        if (nReady == -1) {
            if (errno == EINTR)
                continue;
            err::Exit("select");
        }
        if (nReady == 0)
            continue;
        // 先处理listenfd
        if (FD_ISSET(listenfd, &readSet)) {
            if ((connfd = accept(listenfd, (struct sockaddr*)&peeraddr, &peerlen)) < 0)
                err::Exit("accept");
            int i = 0;
            for (; i < FD_SETSIZE; ++i) {
                if (client[i] < 0) {
                    client[i] = connfd;
                    if (i > maxclient)
                        maxclient = i;
                    break;
                }
            }
            if (i == FD_SETSIZE)
                err::Exit("too many clients");
            printf("count: %d, ip: %s, port: %d\n", ++count, inet_ntoa(peeraddr.sin_addr), ntohs(peeraddr.sin_port));
            FD_SET(connfd, &allSet);
            if (connfd > maxfd)
                maxfd = connfd;
            if (--nReady <= 0)
                continue;
        }
        // 处理已连接套接口的可读事件
        for (int i = 0; i <= maxclient; ++i) {
            if ((connfd = client[i]) == -1)
                continue;
            if (FD_ISSET(connfd, &readSet)) {
                char recvbuf[1024] = {0};
                int ret = readline(connfd, recvbuf, sizeof(recvbuf));
                if (ret == -1)
                    err::Exit("readline");
                if (ret == 0) {
                    printf("client close\n");
                    FD_CLR(connfd, &allSet);
                    client[i] = -1;
                    close(connfd);
                }
                fputs(recvbuf, stdout);
                sleep(4);
                writen(connfd, recvbuf, strlen(recvbuf));
                if (--nReady <= 0)
                    break;
            }
        }
    }

    return 0;
}
