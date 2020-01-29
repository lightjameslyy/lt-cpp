#include "lnp_lt.h"

using namespace lt;

static void handler(int sig) {
    printf("receive sig=%d\n", sig);
    exit(EXIT_SUCCESS);
}

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

    pid_t pid = fork();
    if (pid == -1)
        err::Exit("fork");
    if (pid == 0) {  // send data in child process
        signal(SIGUSR1, handler);
        char sendbuf[1024] = {0};
        while(fgets(sendbuf, sizeof(sendbuf), stdin) != NULL) {
            write(clientfd, sendbuf, strlen(sendbuf));
            memset(sendbuf, 0, sizeof(sendbuf));
        }
        printf("child close\n");
    } else {    // receive data in parent process
        char recvbuf[1024];
        while(1) {
            memset(recvbuf, 0, sizeof(recvbuf));
            int ret = read(clientfd, recvbuf, sizeof(recvbuf));
            if (ret == -1)
                err::Exit("read");
            if (ret == 0) {
                printf("peer close\n");
                break;
            }
            fputs(recvbuf, stdout);
        }
        printf("parent close\n");
        kill(pid, SIGUSR1);
    }

    close(clientfd);

    return 0;
}
