#include "lnp_lt.h"

using namespace lt;

int main(int argc, char* argv[]) {

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <len> <type>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int len = atoi(argv[1]);
    int type = atoi(argv[2]);

    int msqid = msgget(1234,  0 );
    if (msqid == -1)
        err::Exit("msgget");
    printf("msgget success, msqid=%d\n", msqid);

    struct msgbuf* ptr = (struct msgbuf*)malloc(sizeof(long) + len);
    ptr->mtype = type;
    int ret = msgsnd(msqid, ptr, len, IPC_NOWAIT);
    if (ret == -1)
        err::Exit("msgsnd");

    return 0;
}
