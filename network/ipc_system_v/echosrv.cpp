#include "lnp_lt.h"

using namespace lt;

static const size_t MSGMAX = 8192;

struct msgbufm {
    long mtype;
    char mtext[MSGMAX];
};

static void echo_server(int msqid) {
    msgbufm msg;
    memset(&msg, 0, sizeof(msg));
    while(1) {
        int ret = msgrcv(msqid, &msg, MSGMAX, 1, 0);
        if (ret == -1)
            err::Exit("msgrcv");

        int pid = *((int*)msg.mtext);   // client的pid

        fflush(stdout);
        fputs(msg.mtext + 4, stdout);
        msg.mtype = pid;
        msgsnd(msqid, &msg, ret, 0);
    }
}

int main(int argc, char* argv[]) {

    int msqid = msgget(1234,  0666 | IPC_CREAT);
    if (msqid == -1)
        err::Exit("msgget");
    printf("msgget success, msqid=%d\n", msqid);

    echo_server(msqid);

    return 0;
}
