/*
 * test *_timeout
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


    int ret = connect_timeout(clientfd, &servaddr, 5);
    if (ret == -1 && errno == ETIMEDOUT) {
        printf("timeout ...\n");
        return 1;
    }
    if (ret == -1)
        err::Exit("connect_timeout");

    struct sockaddr_in localaddr;
    socklen_t addrlen = sizeof(localaddr);
    if (getsockname(clientfd, (struct sockaddr*)&localaddr, &addrlen) < 0)
        err::Exit("getsockname");

    printf("ip: %s, port: %d\n", inet_ntoa(localaddr.sin_addr), ntohs(localaddr.sin_port));

    return 0;
}
