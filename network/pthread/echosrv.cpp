/*
 * proccess per connection
 * using readline
 * ignore SIGCHLD signal
 */

#include "lnp_lt.h"

using namespace lt;

static void echo_server(int connfd) {
    char recvbuf[1024];
    while(1) {
        memset(&recvbuf, 0, sizeof(recvbuf));
        int ret = readline(connfd, recvbuf, sizeof(recvbuf));
        if (ret == -1)
            err::Exit("readline");
        if (ret == 0) {
            printf("client close\n");
            break;
        }
        fputs(recvbuf, stdout);
        writen(connfd, recvbuf, strlen(recvbuf));
    }
    close(connfd);
}

static void sigchld_handler(int sig) {
    //wait(NULL); // 捕获子进程的推出状态，只能捕获一个子进程
    while (waitpid(-1, NULL, WNOHANG) > 0);
}

static void* thread_routine(void* arg) {
    pthread_detach(pthread_self());
    int connfd = *(int*)arg;
    free((int*)arg);
    echo_server(connfd);
    printf("exiting thread...\n");
    return NULL;
}

int main(int argc, char* argv[]) {
    //signal(SIGCHLD, SIG_IGN);
    signal(SIGCHLD, sigchld_handler);
    int listenfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (listenfd < 0)
        err::Exit("socket");

    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(5188);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);   // 0.0.0.0, for server

    int on = 1;
    if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0)
        err::Exit("setsockopt");

    if (bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)
        err::Exit("bind");

    if (listen(listenfd, SOMAXCONN) < 0)
        err::Exit("listen");

    struct sockaddr_in peeraddr;
    socklen_t peerlen = sizeof(peeraddr);
    int connfd;
    while(1) {
        if ((connfd = accept(listenfd, (struct sockaddr*)&peeraddr, &peerlen)) < 0)
            err::Exit("accept");

        printf("ip: %s, port: %d\n", inet_ntoa(peeraddr.sin_addr), ntohs(peeraddr.sin_port));

        int* p = (int*)malloc(sizeof(int));
        *p = connfd;
        pthread_t tid;
        int ret = pthread_create(&tid, NULL, thread_routine, p);
        if (ret != 0) {
            fprintf(stderr, "pthread_create:%s\n", strerror(ret));
            exit(EXIT_FAILURE);
        }

        /*
        pid_t pid = fork();
        if (pid == -1)
            err::Exit("fork");
        if (pid == 0) { // in child process
            close(listenfd);
            echo_server(connfd);
            return 0;
        } else {    // in parent process
            close(connfd);
        }
        */
    }

    close(listenfd);

    return 0;
}
