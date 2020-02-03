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

    printf("mode=%o\n", buf.msg_perm.mode);
    printf("bytes=%ld\n", buf.__msg_cbytes);
    printf("qnum=%ld\n", buf.msg_qnum);
    printf("qbytes=%ld\n", buf.msg_qbytes);

    return 0;
}
