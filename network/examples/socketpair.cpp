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
        close(sockfds[1]);
        int val = 0;
        while(1) {
            ++val;
            printf("sending data: %d\n", val);
            write(sockfds[0], &val, sizeof(val));
            read(sockfds[0], &val, sizeof(val));
            printf("data received: %d\n", val);
            sleep(1);
        }
    } else if (pid > 0) {  // parent process
        close(sockfds[0]);
        int val;
        while(1) {
            read(sockfds[1], &val, sizeof(val));
            ++val;
            write(sockfds[1], &val, sizeof(val));
        }
    }

    return 0;
}
