/*
 * Linux Network Programming header file by liutao.
 */

#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <sys/resource.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <errno.h>
#include <netdb.h>
#include <poll.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <vector>
#include <algorithm>

namespace lt {

bool isHostBigEndian();

template<size_t N>
struct EchoPacket {
    int len;
    char buf[N];
};

ssize_t readn(int fd, void* buf, size_t count);
ssize_t writen(int fd, const void* buf, size_t count);

ssize_t recvpeek(int sockfd, void* buf, size_t len);

ssize_t readline(int sockfd, void* buf, size_t maxlen);

void activate_nonblock(int fd);
void deactivate_nonblock(int fd);

int read_timeout(int fd, unsigned int wait_seconds);
int write_timeout(int fd, unsigned int wait_seconds);
int accept_timeout(int fd, struct sockaddr_in* addr, unsigned int wait_seconds);
int connect_timeout(int fd, struct sockaddr_in* addr, unsigned int wait_seconds);

// epoll
namespace epoll {

typedef std::vector<struct epoll_event> EventList;

}   // namespace epoll

// info
namespace info {

// 获取本机IP地址，默认返回第一个IP地址
inline int getlocalip(char* ip) {
    char host[100] = {0};
    if (gethostname(host, sizeof(host)) < 0)
        return -1;
    struct hostent* hp;
    if ((hp = gethostbyname(host)) == NULL)
        return -1;
    strcpy(ip, inet_ntoa(*(struct in_addr*)hp->h_addr_list[0]));
    return 0;
}

}   // namespace info

// errors
namespace err {

inline void Exit(const char* fmt) {
    perror(fmt);
    exit(EXIT_FAILURE);
}

}   // namespace err

}   // namespace lt
