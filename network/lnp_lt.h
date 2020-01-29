/*
 * Linux Network Programming header file by liutao.
 */

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <errno.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

namespace lt {

bool isHostBigEndian();

template<size_t N>
struct EchoPacket {
    int len;
    char buf[N]; 
};

ssize_t readn(int fd, void *buf, size_t count);
ssize_t writen(int fd, const void *buf, size_t count);

// errors
namespace err {

inline void Exit(const char* fmt) {
    perror(fmt);
    exit(EXIT_FAILURE);
}

}   // namespace err

}   // namespace lt
