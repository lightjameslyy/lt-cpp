#include <stdio.h>

int main(void) {
    signal(SIGPIPE, SIG_IGN);   // 忽略SIGPIPE信号，防止进程terminate
    signal(SIGCHLD, SIG_IGN);   // 避免子进程成为僵尸进程

    int listenfd;

    if ((listenfd = socket(PF_INET, SOCK_STREAM | SOCK_NONBLOCK | SOCK_CLOEXEC, IPPROTO_TCP)) < 0)
        ERR_EXIT("socket");


}
