/*
 * test select limit
 */
#include "lnp_lt.h"

using namespace lt;

int main(int argc, char* argv[]) {
    int count = 0;
    while (1) {
        int clientfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (clientfd < 0) {
            // 推迟发送FIN段给对方
            sleep(4);
            err::Exit("socket");
        }

        struct sockaddr_in servaddr;
        memset(&servaddr, 0, sizeof(servaddr));
        servaddr.sin_family = AF_INET;
        servaddr.sin_port = htons(5188);
        servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

        if (connect(clientfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)
            err::Exit("connect");

        struct sockaddr_in localaddr;
        socklen_t addrlen = sizeof(localaddr);
        if (getsockname(clientfd, (struct sockaddr*)&localaddr, &addrlen) < 0)
            err::Exit("getsockname");

        printf("count: %d, ip: %s, port: %d\n", ++count, inet_ntoa(localaddr.sin_addr), ntohs(localaddr.sin_port));

    }

    return 0;
}
