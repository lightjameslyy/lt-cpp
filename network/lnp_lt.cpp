#include "lnp_lt.h"

namespace lt {

bool isHostBigEndian() {
    unsigned int val = 0x12345678;
    unsigned char* p = (unsigned char*)&val;
    return p[0] == 0x12;
}

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

ssize_t recvpeek(int sockfd, void* buf, size_t len) {
    while(1) {
        int ret = recv(sockfd, buf, len, MSG_PEEK);
        if(ret == -1 && errno == EINTR)
            continue;
        return ret;
    }
}

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

}   // namespace lt
