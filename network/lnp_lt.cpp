#include "lnp_lt.h"

namespace lt {

/**
 * isHostBigEndian
 * 返回值：大端序返回true，小端序返回false
 */
bool isHostBigEndian() {
    unsigned int val = 0x12345678;
    unsigned char* p = (unsigned char*)&val;
    return p[0] == 0x12;
}

/**
 * readn - read n bytes
 * @fd: 文件描述符
 * @buf: 存放读取的数据
 * @count: 希望读取的字节个数
 * 返回值：读取正常或在读到count个字节之前读到EOF，返回读取字节个数；读取失败，返回-1
 */
ssize_t readn(int fd, void* buf, size_t count) {
    size_t nLeft = count;
    ssize_t nRead;
    char* bufp = (char*)buf;
    while (nLeft > 0) {
        if ((nRead = read(fd, bufp, nLeft)) < 0) {
            if (errno == EINTR) // interupt
                continue;
            return -1;  // other errors
        }
        if (nRead == 0) // EOF
            return count - nLeft;
        bufp += nRead;
        nLeft -= nRead;
    }
    return count;
}

/**
 * writen - write n bytes
 * @fd: 文件描述符
 * @buf: 存放要写的数据
 * @count: 希望写的字节个数
 * 返回值：成功写入，返回count；写入失败，返回-1
 */
ssize_t writen(int fd, const void* buf, size_t count) {
    size_t nLeft = count;
    ssize_t nWritten;
    const char* bufp = (char*)buf;
    while (nLeft > 0) {
        if ((nWritten = write(fd, bufp, nLeft)) < 0) {
            if (errno == EINTR) // interupt
                continue;
            return -1;  // other errors
        }
        if (nWritten == 0)
            continue;
        bufp += nWritten;
        nLeft -= nWritten;
    }
    return count;
}

/**
 * recvpeek - 从套接口接收数据，但是不将缓冲区中的数据移除
 * @sockfd: 套接字
 * @buf：存放peek到的数据
 * @len：要peek的长度
 * 返回值：peek到的字节数，可能小于len
 */
ssize_t recvpeek(int sockfd, void* buf, size_t len) {
    while(1) {
        int ret = recv(sockfd, buf, len, MSG_PEEK);
        if(ret == -1 && errno == EINTR)
            continue;
        return ret;
    }
}

/**
 * readline - 读取一行
 * @sockfd: 套接字
 * @buf：存放读到的数据
 * @maxlen：行的最大长度
 * 返回值：成功，返回读取的行的长度；失败，返回-1
 */
ssize_t readline(int sockfd, void* buf, size_t maxlen) {
    int nRead;
    int nLeft = maxlen;
    char* bufp = (char*)buf;
    while (1) {
        int ret = recvpeek(sockfd, bufp, nLeft);
        if (ret < 0)
            return ret;
        if (ret == 0)
            return ret;
        nRead = ret;
        for (int i = 0; i < nRead; ++i) {
            if (bufp[i] == '\n') {
                ret = readn(sockfd, bufp, i + 1);
                if (ret != i + 1)
                    err::Exit("readn");
                return ret;
            }
        }
        if (nRead > nLeft)
            exit(EXIT_FAILURE);
        nLeft -= nRead;
        ret = readn(sockfd, bufp, nRead);
        if (ret != nRead)
            err::Exit("readn");
        bufp += nRead;
    }
    return -1;
}

/**
 * activate_nonblock - 将fd设置为I/O非阻塞模式
 * @fd: 文件描述符
 */
void activate_nonblock(int fd) {
    int flags = fcntl(fd, F_GETFL);
    if (flags == -1)
        err::Exit("fcntl");
    if (fcntl(fd, F_SETFL, flags | O_NONBLOCK) == -1)
        err::Exit("fcntl");
}

/**
 * deactivate_nonblock - 将fd设置为I/O阻塞模式
 * @fd: 文件描述符
 */
void deactivate_nonblock(int fd) {
    int flags = fcntl(fd, F_GETFL);
    if (flags == -1)
        err::Exit("fcntl");
    if (fcntl(fd, F_SETFL, flags & (~O_NONBLOCK)) == -1)
        err::Exit("fcntl");
}

/**
 * read_timeout - 读超时监测函数，不含读操作
 * @fd: 文件描述符
 * @wait_seconds：等待超时秒数，为0表示不检测超时
 * 返回值：成功（未超时），返回0；失败返回-1；超时也返回-1，同时置errno=ETIMEDOUT
 */
int read_timeout(int fd, unsigned int wait_seconds) {
    int ret = 0;
    if (wait_seconds > 0) {
        fd_set read_fdset;
        FD_ZERO(&read_fdset);
        FD_SET(fd, &read_fdset);

        struct timeval timeout;
        timeout.tv_sec = wait_seconds;
        timeout.tv_usec = 0;

        do {
            ret = select(fd + 1, &read_fdset, NULL, NULL, &timeout);
        } while(ret < 0 && errno == EINTR);

        if (ret == 0) { // 超时
            ret = -1;
            errno = ETIMEDOUT;
        } else if (ret = 1)
            ret = 0;
    }
    return ret;
}

/**
 * write_timeout - 写超时监测函数，不含写操作
 * @fd: 文件描述符
 * @wait_seconds：等待超时秒数，为0表示不检测超时
 * 返回值：成功（未超时），返回0；失败返回-1；超时也返回-1，同时置errno=ETIMEDOUT
 */
int write_timeout(int fd, unsigned int wait_seconds) {
    int ret = 0;
    if (wait_seconds > 0) {
        fd_set wite_fdset;
        FD_ZERO(&wite_fdset);
        FD_SET(fd, &wite_fdset);

        struct timeval timeout;
        timeout.tv_sec = wait_seconds;
        timeout.tv_usec = 0;

        do {
            ret = select(fd + 1, &wite_fdset, NULL, NULL, &timeout);
        } while(ret < 0 && errno == EINTR);

        if (ret == 0) { // 超时
            ret = -1;
            errno = ETIMEDOUT;
        } else if (ret = 1)
            ret = 0;
    }
    return ret;
}

/**
 * accept_timeout - 带超时的accept，包含accept操作
 * @fd: 文件描述符
 * @addr：输出参数，返回对方地址
 * @wait_seconds：等待超时秒数，为0表示不检测超时
 * 返回值：成功（未超时），返回已连接套接字；失败返回-1；超时返回-1，同时置errno=ETIMEDOUT
 */
int accept_timeout(int fd, struct sockaddr_in* addr, unsigned int wait_seconds) {
    int ret;
    socklen_t addrlen = sizeof(struct sockaddr_in);

    if (wait_seconds > 0) {
        fd_set accept_fdset;
        FD_ZERO(&accept_fdset);
        FD_SET(fd, &accept_fdset);

        struct timeval timeout;
        timeout.tv_sec = wait_seconds;
        timeout.tv_usec = 0;

        do {
            ret = select(fd + 1, &accept_fdset, NULL, NULL, &timeout);
        } while(ret < 0 && errno == EINTR);
        if (ret == -1)
            return -1;
        if (ret == 0) {
            errno = ETIMEDOUT;
            return -1;
        }
        // ret = 1 here
    }

    if (addr != NULL)
        ret = accept(fd, (struct sockaddr*)addr, &addrlen);
    else
        ret = accept(fd, NULL, NULL);
    if (ret == -1)
        err::Exit("accept");

    return ret;
}

/**
 * connect_timeout - 带超时的connect，包含connect操作
 * @fd: 文件描述符
 * @addr：输入参数，要连接的对方地址
 * @wait_seconds：等待超时秒数，为0表示不检测超时
 * 返回值：成功（未超时），返回已连接套接字；失败返回-1；超时返回-1，同时置errno=ETIMEDOUT
 */
int connect_timeout(int fd, struct sockaddr_in* addr, unsigned int wait_seconds) {
    int ret;
    socklen_t addrlen = sizeof(struct sockaddr_in);

    if (wait_seconds > 0)
        activate_nonblock(fd);

    ret = connect(fd, (struct sockaddr*)addr, addrlen);
    // if ret == 0, connected
    if (ret < 0 && errno == EINPROGRESS) {  // 正在处理中
        fd_set connect_fdset;
        FD_ZERO(&connect_fdset);
        FD_SET(fd, &connect_fdset);

        struct timeval timeout;
        timeout.tv_sec = wait_seconds;
        timeout.tv_usec = 0;

        do {
            // 一旦连接建立，套接字就可写
            ret = select(fd + 1, NULL, &connect_fdset, NULL, &timeout);
        } while(ret < 0 && errno == EINTR);
        if (ret == 0) {
            ret = -1;
            errno = ETIMEDOUT;
        } else if (ret < 0)
            return -1;
        else if (ret = 1) {
            // 两种情况（产生可写事件）：
            // 1. 套接字连接成功
            // 2. 套接字产生错误（此时错误信息不在errno变量中，需要用getsockopt获取）
            int err;
            socklen_t socklen = sizeof(err);
            if (getsockopt(fd, SOL_SOCKET, SO_ERROR, &err, &socklen) == -1)
                return -1;
            if (err == 0)
                ret = 0;
            else {
                errno = err;
                ret = -1;
            }
        }
    }

    if (wait_seconds > 0)
        deactivate_nonblock(fd);

    return ret;
}

/**
 * send_fd - 发送描述符字
 * @sockfd: 套接字
 * @sendfd: 要发送的描述符字
 */
void send_fd(int sockfd, int sendfd) {
    struct msghdr msg;

    msg.msg_name = NULL;
    msg.msg_namelen = 0;
    char sendchar = 0;
    struct iovec vec;
    vec.iov_base = &sendchar;
    vec.iov_len = sizeof(sendchar);
    msg.msg_iov = &vec;
    msg.msg_iovlen = 1;
    msg.msg_flags = 0;

    char cmsgbuf[CMSG_SPACE(sizeof(sendfd))];
    msg.msg_control = cmsgbuf;
    msg.msg_controllen = sizeof(cmsgbuf);
    struct cmsghdr* p_cmsg = CMSG_FIRSTHDR(&msg);
    p_cmsg->cmsg_level = SOL_SOCKET;
    p_cmsg->cmsg_type = SCM_RIGHTS;
    p_cmsg->cmsg_len = CMSG_LEN(sizeof(sendfd));
    int* p_fds = (int*)CMSG_DATA(p_cmsg);
    *p_fds = sendfd;

    int ret = sendmsg(sockfd, &msg, 0);
    if (ret != 1)
        err::Exit("sendmsg");
}

/**
 * recv_fd - 接收描述符字
 * @sockfd: 套接字
 * 返回值：接收到的描述符字
 */
int recv_fd(int sockfd) {
    int recvfd;
    char recvchar = 0;
    struct msghdr msg;
    msg.msg_name = NULL;
    msg.msg_namelen = 0;
    struct iovec vec;
    vec.iov_base = &recvchar;
    vec.iov_len = sizeof(recvchar);
    msg.msg_iov = &vec;
    msg.msg_iovlen = 1;
    msg.msg_flags = 0;

    char cmsgbuf[CMSG_SPACE(sizeof(recvfd))];
    msg.msg_control = cmsgbuf;
    msg.msg_controllen = sizeof(cmsgbuf);
    int* p_fds = (int*)CMSG_DATA(CMSG_FIRSTHDR(&msg));
    *p_fds = -1;

    int ret = recvmsg(sockfd, &msg, 0);
    if (ret != 1)
        err::Exit("recvmsg");

    struct cmsghdr* p_cmsg = CMSG_FIRSTHDR(&msg);
    if (p_cmsg == NULL)
        err::Exit("np passed fd");

    p_fds = (int*)CMSG_DATA(p_cmsg);
    recvfd = *p_fds;
    if (recvfd == -1)
        err::Exit("no passed fd");

    return recvfd;

}


}   // namespace lt
