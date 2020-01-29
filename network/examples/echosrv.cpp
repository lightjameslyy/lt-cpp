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
    if ((connfd = accept(listenfd, (struct sockaddr*)&peeraddr, &peerlen)) < 0)
        err::Exit("accept");

    printf("ip: %s, port: %d\n", inet_ntoa(peeraddr.sin_addr), ntohs(peeraddr.sin_port));

    char recvbuf[1024] = {0};
    while(1) {
        memset(recvbuf, 0, sizeof(recvbuf));
        int ret = read(connfd, recvbuf, sizeof(recvbuf));
        if (ret == 0)
            break;
        fputs(recvbuf, stdout);
        write(connfd, recvbuf, ret);
    }

    close(connfd);
    close(listenfd);

    return 0;
}
