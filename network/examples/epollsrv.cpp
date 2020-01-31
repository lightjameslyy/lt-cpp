/*
 * epoll server
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

static void sigpipe_handler(int sig) {
    printf("receive signal=%d\n", sig);
}

int main(int argc, char* argv[]) {
    signal(SIGPIPE, sigpipe_handler);
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
    //servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    //inet_aton("127.0.0.1", &servaddr.sin_addr);

    int on = 1;
    if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0)
        err::Exit("setsockopt");

    if (bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)
        err::Exit("bind");

    if (listen(listenfd, SOMAXCONN) < 0)
        err::Exit("listen");

    std::vector<int> clients;
    // old: epoll_create()使用hash table
    // prefered: epoll_create1()使用红黑树
    int epollfd = epoll_create1(EPOLL_CLOEXEC);

    struct epoll_event event;
    event.data.fd = listenfd;
    event.events = EPOLLIN | EPOLLET;
    epoll_ctl(epollfd, EPOLL_CTL_ADD, listenfd, &event);

    epoll::EventList events(16);
    struct sockaddr_in peeraddr;
    socklen_t peerlen = sizeof(peeraddr);
    int connfd;

    int count = 0;
    while (1) {
        int nReady = epoll_wait(epollfd, &*events.begin(), static_cast<int>(events.size()), -1);
        if (nReady == -1) {
            if (errno == EINTR) // 中断
                continue;
            err::Exit("select");
        }
        if (nReady == 0)    // 超时
            continue;
        if ((size_t)nReady == events.size())
            events.resize(events.size() * 2);
        for (int i = 0; i < nReady; ++i) {
            if (events[i].data.fd == listenfd) {    // 先处理listenfd
                if ((connfd = accept(listenfd, (struct sockaddr*)&peeraddr, &peerlen)) < 0)
                    err::Exit("accept");

                printf("count: %d, ip: %s, port: %d\n", ++count, inet_ntoa(peeraddr.sin_addr), ntohs(peeraddr.sin_port));

                clients.push_back(connfd);
                activate_nonblock(connfd);

                event.data.fd = connfd;
                event.events = EPOLLIN | EPOLLET;
                epoll_ctl(epollfd, EPOLL_CTL_ADD, connfd, &event);

            } else if (events[i].events & EPOLLIN) {    // 处理已连接套接口的可读事件
                if ((connfd = events[i].data.fd) < 0)
                    continue;
                char recvbuf[1024] = {0};
                int ret = readline(connfd, recvbuf, sizeof(recvbuf));
                if (ret == -1)
                    err::Exit("readline");
                if (ret == 0) {
                    printf("client close\n");
                    close(connfd);

                    event = events[i];
                    epoll_ctl(epollfd, EPOLL_CTL_DEL, connfd, &event);
                    clients.erase(std::remove(clients.begin(), clients.end(), connfd), clients.end());
                }
                fputs(recvbuf, stdout);
                writen(connfd, recvbuf, strlen(recvbuf));
            }
        }
    }

    return 0;
}
