#include "lnp_lt.h"

using namespace lt;

int main(int argc, char* argv[]) {

    int msqid = msgget(1234, 0666 | IPC_CREAT);
    if (msqid == -1)
        err::Exit("msgget");
    printf("msgget success, msqid=%d\n", msqid);

    struct msqid_ds buf;
    int ret = msgctl(msqid, IPC_STAT, &buf);
    if (ret == -1)
        err::Exit("msgctl");

    buf.msg_perm.mode = 0600;

    ret = msgctl(msqid, IPC_SET, &buf);
    if (ret == -1)
        err::Exit("msgctl");

    return 0;
}
