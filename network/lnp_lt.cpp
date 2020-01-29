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

}   // namespace lt
