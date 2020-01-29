/*
 * using readn and writen
 * using user-defined packet
 */
#include "lnp_lt.h"

using namespace lt;

int main(int argc, char* argv[]) {
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

    EchoPacket<1024> recvbuf;
    EchoPacket<1024> sendbuf;
    int len;
    while(fgets(sendbuf.buf, sizeof(sendbuf.buf), stdin) != NULL) {
        len = strlen(sendbuf.buf);
        sendbuf.len = htonl(len);
        writen(clientfd, &sendbuf, 4 + len);
        int ret = readn(clientfd, &recvbuf.len, 4);
        if (ret == -1)
            err::Exit("read");
        if (ret < 4) {
            printf("server close\n");
            break;
        }
        len = ntohl(recvbuf.len);
        ret = readn(clientfd, recvbuf.buf, len);
        if (ret == -1)
            err::Exit("read");
        if (ret < len) {
            printf("server close\n");
            break;
        }
        fputs(recvbuf.buf, stdout);
        memset(&recvbuf, 0, sizeof(recvbuf));
        memset(&sendbuf, 0, sizeof(sendbuf));
    }

    close(clientfd);

    return 0;
}
