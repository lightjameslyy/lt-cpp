/*
 * proccess per connection
 * using readn and writen
 * using user-defined packet
 */

#include "lnp_lt.h"

using namespace lt;

static void do_service(int connfd) {
    EchoPacket<1024> recvbuf;
    int len;
    while(1) {
        memset(&recvbuf, 0, sizeof(recvbuf));
        int ret = readn(connfd, &recvbuf.len, 4);
        if (ret == -1)
            err::Exit("read");
        if (ret < 4) {
            printf("client close\n");
            break;
        }
        len = ntohl(recvbuf.len);
        ret = readn(connfd, recvbuf.buf, len);
        if (ret == -1)
            err::Exit("read");
        if (ret < len) {
            printf("client close\n");
            break;
        }
        fputs(recvbuf.buf, stdout);
        writen(connfd, &recvbuf, 4 + ret);
    }
    close(connfd);
}

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
    while(1) {
        if ((connfd = accept(listenfd, (struct sockaddr*)&peeraddr, &peerlen)) < 0)
            err::Exit("accept");

        printf("ip: %s, port: %d\n", inet_ntoa(peeraddr.sin_addr), ntohs(peeraddr.sin_port));

        pid_t pid = fork();

        if (pid == -1)
            err::Exit("fork");
        if (pid == 0) { // in child process
            close(listenfd);
            do_service(connfd);
            return 0;
        } else {    // in parent process
            close(connfd);
        }
    }

    close(listenfd);

    return 0;
}
