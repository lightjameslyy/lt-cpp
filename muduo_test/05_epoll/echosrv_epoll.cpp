#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/epoll.h>

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#include <vector>
#include <algorithm>
#include <iostream>

typedef std::vector<struct epoll_event> EventList;

#define ERR_EXIT(m) \
        do \
        { \
                perror(m); \
                exit(EXIT_FAILURE); \
        } while(0)

int main(void) {
    signal(SIGPIPE, SIG_IGN);   // 忽略SIGPIPE信号，防止进程terminate
    signal(SIGCHLD, SIG_IGN);   // 避免子进程成为僵尸进程

    // 为进程保留一个空闲套接字，用来解决EMFILE问题
    int idlefd = open("/dev/null", O_RDONLY | O_CLOEXEC);
    int listenfd;

    //if ((listenfd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
    if ((listenfd = socket(PF_INET, SOCK_STREAM | SOCK_NONBLOCK | SOCK_CLOEXEC, IPPROTO_TCP)) < 0)
        ERR_EXIT("socket");

    // 填充一个地址
    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(5188);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    // 设置地址重复使用
    int on = 1;
    if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0)
        ERR_EXIT("setsockopt");

    // 绑定
    if (bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)
        ERR_EXIT("bind");
    // 监听
    if (listen(listenfd, SOMAXCONN) < 0)
        ERR_EXIT("listen");

    std::vector<int> clients;
    // 创建epollfd
    int epollfd;
    epollfd = epoll_create1(EPOLL_CLOEXEC);

    // 关注listenfd的可读事件
    struct epoll_event event;
    event.data.fd = listenfd;
    event.events = EPOLLIN/* | EPOLLET*/;   // 默认是EPOLLLT
    epoll_ctl(epollfd, EPOLL_CTL_ADD, listenfd, &event);

    // 事件列表
    EventList events(16);
    struct sockaddr_in peeraddr;
    socklen_t peerlen;
    int connfd;

    int nready;
    while (1) {
        nready = epoll_wait(epollfd, &*events.begin(), static_cast<int>(events.size()), -1);
        if (nready == -1) {
            if (errno == EINTR)
                continue;

            ERR_EXIT("epoll_wait");
        }
        if (nready == 0)	// nothing happended
            continue;

        // 调整事件列表的容量
        if ((size_t)nready == events.size())
            events.resize(events.size()*2);

        for (int i = 0; i < nready; ++i) {
            if (events[i].data.fd == listenfd) { // 监听套接字活跃
                peerlen = sizeof(peeraddr);
                connfd = ::accept4(listenfd, (struct sockaddr*)&peeraddr,
                                   &peerlen, SOCK_NONBLOCK | SOCK_CLOEXEC);

                if (connfd == -1) {
                    if (errno == EMFILE) {  // 处理EMFILE
                        close(idlefd);
                        idlefd = accept(listenfd, NULL, NULL);
                        close(idlefd);
                        idlefd = open("/dev/null", O_RDONLY | O_CLOEXEC);
                        continue;
                    } else
                        ERR_EXIT("accept4");
                }


                std::cout<<"ip="<<inet_ntoa(peeraddr.sin_addr)<<
                         " port="<<ntohs(peeraddr.sin_port)<<std::endl;

                clients.push_back(connfd);

                event.data.fd = connfd;
                event.events = EPOLLIN/* | EPOLLET*/;
                // 加入关注
                epoll_ctl(epollfd, EPOLL_CTL_ADD, connfd, &event);
            } else if (events[i].events & EPOLLIN) { // 处理活跃套接字
                connfd = events[i].data.fd;
                if (connfd < 0)
                    continue;

                char buf[1024] = {0};
                int ret = read(connfd, buf, 1024);
                if (ret == -1)
                    ERR_EXIT("read");
                if (ret == 0) {
                    std::cout<<"client close"<<std::endl;
                    close(connfd);
                    event = events[i];
                    // 连接关闭后，把对应的套接字剔除关注
                    epoll_ctl(epollfd, EPOLL_CTL_DEL, connfd, &event);
                    clients.erase(std::remove(clients.begin(), clients.end(), connfd), clients.end());
                    continue;
                }

                std::cout<<buf;
                write(connfd, buf, strlen(buf));
            }

        }
    }

    return 0;
}
