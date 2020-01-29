/*
 * using readn and writen
 * 跟echosrv3.cpp协议使用定长包大小
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

    char sendbuf[1024] = {0};
    char recvbuf[1024] = {0};
    while(fgets(sendbuf, sizeof(sendbuf), stdin) != NULL) {
        //write(clientfd, sendbuf, strlen(sendbuf));
        writen(clientfd, sendbuf, sizeof(sendbuf));
        readn(clientfd, recvbuf, sizeof(recvbuf));
        fputs(recvbuf, stdout);
        memset(recvbuf, 0, sizeof(recvbuf));
        memset(sendbuf, 0, sizeof(sendbuf));
    }

    close(clientfd);

    return 0;
}
