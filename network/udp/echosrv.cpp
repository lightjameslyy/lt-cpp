/*
 * echo server using UDP
 */

#include "lnp_lt.h"

using namespace lt;

static void echo_server(int sock) {
    char recvbuf[1024];
    struct sockaddr_in peeraddr;
    socklen_t peerlen = sizeof(peeraddr);
    while(1) {
        memset(&recvbuf, 0, sizeof(recvbuf));
        int ret = recvfrom(sock, recvbuf, sizeof(recvbuf), 0, (struct sockaddr*)&peeraddr, &peerlen);
        if (ret == -1) {
            if (errno == EINTR)
                continue;
            err::Exit("recvfrom");
        }
        if (ret == 0) {
            printf("client close\n");
            break;
        }
        fputs(recvbuf, stdout);
        sendto(sock, recvbuf, ret, 0, (struct sockaddr*)&peeraddr, peerlen);
    }
    close(sock);
}

int main(int argc, char* argv[]) {
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0)
        err::Exit("socket");

    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(5188);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);   // 0.0.0.0, for server

    //int on = 1;
    //if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0)
    //    err::Exit("setsockopt");

    if (bind(sock, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)
        err::Exit("bind");

    echo_server(sock);

    return 0;
}
