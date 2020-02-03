#include "lnp_lt.h"

using namespace lt;

static const size_t MSGMAX = 8192;

int main(int argc, char* argv[]) {

    int flags = 0;
    int type = 0;

    while(1) {
        int opt = getopt(argc, argv, "nt:");
        if (opt == -1)
            break;
        if (opt == '?')
            exit(EXIT_FAILURE);

        switch (opt) {
        case 'n':
            flags |= IPC_NOWAIT;
            break;
        case 't':
            type = atoi(optarg);
            break;
        }
    }

    int msqid = msgget(1234,  0 );
    if (msqid == -1)
        err::Exit("msgget");
    printf("msgget success, msqid=%d\n", msqid);

    struct msgbuf* ptr = (struct msgbuf*)malloc(sizeof(long) + MSGMAX);
    ptr->mtype = type;
    int ret = msgrcv(msqid, ptr, MSGMAX, type, flags);
    if (ret == -1)
        err::Exit("msgrcv");

    printf("read %d bytes, type=%ld\n", ret, ptr->mtype);

    return 0;
}
