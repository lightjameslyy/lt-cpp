/*
 * echo client using UDP
 * UDP connect()
 */

#include "lnp_lt.h"

using namespace lt;

static void echo_client(int sock) {
    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(5188);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sock, (struct sockaddr*)&servaddr, sizeof(servaddr));

    char sendbuf[1024] = {0};
    char recvbuf[1024] = {0};
    while(fgets(sendbuf, sizeof(sendbuf), stdin) != NULL) {
        //sendto(sock, sendbuf, strlen(sendbuf), 0, (struct sockaddr*)&servaddr, sizeof(servaddr));
        //sendto(sock, sendbuf, strlen(sendbuf), 0, NULL, 0); // 已经通过connect绑定远程地址
        send(sock, sendbuf, strlen(sendbuf), 0); // 已经通过connect绑定远程地址
        int ret = recvfrom(sock, recvbuf, sizeof(recvbuf), 0, NULL, NULL);
        if (ret == -1) {
            if (errno == EINTR)
                continue;
            err::Exit("recvfrom");
        }
        fputs(recvbuf, stdout);
        memset(recvbuf, 0, sizeof(recvbuf));
        memset(sendbuf, 0, sizeof(sendbuf));
    }
    close(sock);
}

int main(int argc, char* argv[]) {
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0)
        err::Exit("socket");

    echo_client(sock);

    return 0;
}
