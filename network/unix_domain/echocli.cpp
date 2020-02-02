#include "lnp_lt.h"

using namespace lt;

static void echo_client(int sock) {
    char sendbuf[1024] = {0};
    char recvbuf[1024] = {0};
    while(fgets(sendbuf, sizeof(sendbuf), stdin) != NULL) {
        write(sock, sendbuf, strlen(sendbuf));
        read(sock, recvbuf, sizeof(recvbuf));
        fputs(recvbuf, stdout);
        memset(recvbuf, 0, sizeof(recvbuf));
        //memset(sendbuf, 0, sizeof(sendbuf));
    }
    close(sock);
}

int main(int argc, char* argv[]) {
    int clientfd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (clientfd < 0)
        err::Exit("socket");

    struct sockaddr_un servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sun_family = AF_UNIX;
    strcpy(servaddr.sun_path, "/tmp/test_socket");

    if (connect(clientfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)
        err::Exit("connect");

    echo_client(clientfd);

    return 0;
}
