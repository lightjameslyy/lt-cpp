/*
 * proccess per connection
 * using readline
 * ignore SIGCHLD signal
 * using select
 * handle SIGPIPE
 * compare close() and shutdown()
 * select -> poll
 */

#include "lnp_lt.h"

using namespace lt;

static void echo_server(int connfd) {
    char recvbuf[1024];
    while(1) {
        memset(&recvbuf, 0, sizeof(recvbuf));
        int ret = readline(connfd, recvbuf, sizeof(recvbuf));
        if (ret == -1)
            err::Exit("readline");
        if (ret == 0) {
            printf("client close\n");
            break;
        }
        fputs(recvbuf, stdout);
        writen(connfd, recvbuf, strlen(recvbuf));
    }
    close(connfd);
}

static void sigchld_handler(int sig) {
    //wait(NULL); // 捕获子进程的推出状态，只能捕获一个子进程
    while (waitpid(-1, NULL, WNOHANG) > 0);
}

static void sigpipe_handler(int sig) {
    printf("receive signal=%d\n", sig);
}

int main(int argc, char* argv[]) {
    signal(SIGPIPE, sigpipe_handler);
    //signal(SIGCHLD, SIG_IGN);
    signal(SIGCHLD, sigchld_handler);
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

    int maxclient = 0;
    struct pollfd client[2048];
    for (int i = 0 ; i < 2048; ++i)
        client[i].fd = -1; // 用-1表示空闲

    int count = 0;
    client[0].fd = listenfd;
    client[0].events = POLLIN;
    while (1) {
        int nReady = poll(client, maxclient + 1, -1); // scan [0, maxclient]
        if (nReady == -1) {
            if (errno == EINTR) // 中断
                continue;
            err::Exit("select");
        }
        if (nReady == 0)    // 超时
            continue;
        // 先处理listenfd
        if (client[0].revents & POLLIN) {
            if ((connfd = accept(listenfd, (struct sockaddr*)&peeraddr, &peerlen)) < 0)
                err::Exit("accept");
            int i = 0;
            for (; i < 2048; ++i) {
                if (client[i].fd < 0) {
                    client[i].fd = connfd;
                    client[i].events = POLLIN;
                    if (i > maxclient)
                        maxclient = i;
                    break;
                }
            }
            if (i == 2048)
                err::Exit("too many clients");
            printf("count: %d, ip: %s, port: %d\n", ++count, inet_ntoa(peeraddr.sin_addr), ntohs(peeraddr.sin_port));
            if (--nReady <= 0)
                continue;
        }
        // 处理已连接套接口的可读事件
        for (int i = 0; i <= maxclient; ++i) {
            if ((connfd = client[i].fd) == -1)
                continue;
            if (client[i].revents & POLLIN) {
                char recvbuf[1024] = {0};
                int ret = readline(connfd, recvbuf, sizeof(recvbuf));
                if (ret == -1)
                    err::Exit("readline");
                if (ret == 0) {
                    printf("client close\n");
                    client[i].fd = -1;
                    close(connfd);
                }
                fputs(recvbuf, stdout);
                writen(connfd, recvbuf, strlen(recvbuf));
                if (--nReady <= 0)
                    break;
            }
        }
    }

    return 0;
}
