#include "lnp_lt.h"

using namespace lt;

static const size_t MSGMAX = 8192;

struct msgbufm {
    long mtype;
    char mtext[MSGMAX];
};

static void echo_client(int msqid) {

    msgbufm msg;
    memset(&msg, 0, sizeof(msg));
    int pid = getpid();
    *((int*)msg.mtext) = pid;
    msg.mtype = 1;
    while(fgets(msg.mtext + 4, MSGMAX - 4, stdin) != NULL) {
        int ret = msgsnd(msqid, &msg, 4 + strlen(msg.mtext + 4), 0);
        if (ret == -1)
            err::Exit("msgsnd");

        memset(msg.mtext + 4, 0, MSGMAX - 4);
        ret = msgrcv(msqid, &msg, MSGMAX, pid, 0);
        if (ret == -1)
            err::Exit("msgrcv");

        fputs(msg.mtext + 4, stdout);
        memset(msg.mtext + 4, 0, MSGMAX - 4);
    }
}

int main(int argc, char* argv[]) {

    int msqid = msgget(1234,  0);
    if (msqid == -1)
        err::Exit("msgget");
    printf("msgget success, msqid=%d\n", msqid);

    echo_client(msqid);

    return 0;
}
