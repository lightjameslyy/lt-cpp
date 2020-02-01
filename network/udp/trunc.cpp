/*
 * truncation in UDP
 */

#include "lnp_lt.h"

using namespace lt;

int main(int argc, char* argv[]) {
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0)
        err::Exit("socket");

    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(5188);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);   // 0.0.0.0, for server

    if (bind(sock, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)
        err::Exit("bind");

    sendto(sock, "ABCD", 4, 0, (struct sockaddr*)&servaddr, sizeof(servaddr));

    char recvbuf[1];
    for (int i = 0; i < 4; ++i) {
        int ret = recvfrom(sock, recvbuf, sizeof(recvbuf), 0, NULL, NULL);
        if (ret == -1) {
            if (errno == EINTR)
                continue;
            err::Exit("recvfrom");
        }
        if (ret > 0) {
            printf("ret=%d %c\n", ret, recvbuf[0]);
        }
    }

    return 0;
}
