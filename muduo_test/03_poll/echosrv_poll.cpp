#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <sys/wait.h>
#include <poll.h>

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#include <vector>
#include <iostream>

#define ERR_EXIT(m) \
        do \
        { \
                perror(m); \
                exit(EXIT_FAILURE); \
        } while(0)

typedef std::vector<struct pollfd> PollFdList;

int main(void) {
    signal(SIGPIPE, SIG_IGN);   // 忽略SIGPIPE信号，防止进程terminate
    signal(SIGCHLD, SIG_IGN);   // 避免子进程成为僵尸进程

    //int idlefd = open("/dev/null", O_RDONLY | O_CLOEXEC);
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

    // 定义pollfd，初始化后绑定listenfd
    struct pollfd pfd;
    pfd.fd = listenfd;
    pfd.events = POLLIN;

    // 存放待处理的pollfd
    PollFdList pollfds;
    pollfds.push_back(pfd);

    int nready;

    struct sockaddr_in peeraddr;
    socklen_t peerlen;
    int connfd;

    while (1) {
        nready = poll(&*pollfds.begin(), pollfds.size(), -1);
        if (nready == -1) {
            // 忽略EINTR信号`
            if (errno == EINTR)
                continue;
            ERR_EXIT("poll");
        }
        if (nready == 0)	// nothing happended
            continue;

        // pollfds[0]对应服务器的listenfd, pollfds[1:n]对应未处理完的connfd
        if (pollfds[0].revents & POLLIN) {
            peerlen = sizeof(peeraddr);
            connfd = accept4(listenfd, (struct sockaddr*)&peeraddr,
                             &peerlen, SOCK_NONBLOCK | SOCK_CLOEXEC);

            if (connfd == -1)
                ERR_EXIT("accept4");

            // 将连接注册到pollfd列表中
            pfd.fd = connfd;
            pfd.events = POLLIN;
            pfd.revents = 0;    // 清空返回事件
            pollfds.push_back(pfd);
            --nready;

            // 连接成功
            std::cout<<"ip="<<inet_ntoa(peeraddr.sin_addr)<<
                     " port="<<ntohs(peeraddr.sin_port)<<std::endl;
            if (nready == 0)
                continue;
        }

        //std::cout<<pollfds.size()<<std::endl;
        //std::cout<<nready<<std::endl;

        // pollfds[1:n]是未处理完的connfd，遍历pollfds并处理这些套接字`
        for (PollFdList::iterator it=pollfds.begin()+1;
                it != pollfds.end() && nready >0; ++it) {
            if (it->revents & POLLIN) {
                --nready;
                connfd = it->fd;
                char buf[1024] = {0};
                int ret = read(connfd, buf, 1024);
                if (ret == -1)
                    ERR_EXIT("read");
                if (ret == 0) {
                    std::cout<<"client close"<<std::endl;
                    it = pollfds.erase(it);
                    --it;

                    close(connfd);
                    continue;
                }

                // 打印client发过来的消息
                std::cout<<buf;
                // 向client回射
                write(connfd, buf, strlen(buf));
            }
        }
    }

    return 0;
}

