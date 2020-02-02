/*
 * test socketpair
 */
#include "lnp_lt.h"

using namespace lt;

int main(int argc, char* argv[]) {
    int sockfds[2];

    if (socketpair(AF_UNIX, SOCK_STREAM, 0, sockfds) < 0)
        err::Exit("socketpair");

    // 下面在父子进程之间实现全双工通信
    pid_t pid = fork();

    if (pid == -1)
        err::Exit("fork");

    if (pid == 0) { // child process
        close(sockfds[0]);
        int fd = open("test.txt", O_RDONLY);
        if (fd == -1)
            err::Exit("open");
        send_fd(sockfds[1], fd);
    } else if (pid > 0) {  // parent process
        close(sockfds[1]);
        int fd = recv_fd(sockfds[0]);
        char buf[1024] = {0};
        read(fd, buf, sizeof(buf));
        printf("buf=%s\n", buf);
    }

    return 0;
}
