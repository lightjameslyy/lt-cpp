#include "lnp_lt.h"

using namespace lt;

static void echo_server(int connfd) {
    char recvbuf[1024] = {0};
    while(1) {
        memset(recvbuf, 0, sizeof(recvbuf));
        int ret = read(connfd, recvbuf, sizeof(recvbuf));
        if (ret == -1) {
            if (errno == EINTR)
                continue;
            err::Exit("read");
        }
        if (ret == 0) {
            printf("client close\n");
            break;
        }
        fputs(recvbuf, stdout);
        write(connfd, recvbuf, ret);
    }
    close(connfd);
}

static void sigint_handler(int sig) {
    unlink("/tmp/test_socket");
    printf("receive sig=%d, server terminating...\n", sig);
    exit(EXIT_SUCCESS);
}

int main(int argc, char* argv[]) {
    signal(SIGINT, sigint_handler);
    int listenfd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (listenfd < 0)
        err::Exit("socket");

    struct sockaddr_un servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sun_family = AF_UNIX;
    strcpy(servaddr.sun_path, "/tmp/test_socket");

    int on = 1;
    if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0)
        err::Exit("setsockopt");

    if (bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)
        err::Exit("bind");

    if (listen(listenfd, SOMAXCONN) < 0)
        err::Exit("listen");

    int connfd;
    while(1) {
        if ((connfd = accept(listenfd, NULL, NULL)) < 0) {
            if (errno == EINTR)
                continue;
            err::Exit("accept");
        }

        pid_t pid = fork();
        if (pid == -1)
            err::Exit("fork");

        if (pid == 0) { // 子进程
            close(listenfd);
            echo_server(connfd);
            exit(EXIT_SUCCESS);
        }

        close(connfd);
    }

    close(listenfd);

    return 0;
}
