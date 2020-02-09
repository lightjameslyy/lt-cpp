#include "lnp_lt.h"

using namespace lt;

int main(int argc, char* argv[]) {

    int msqid = msgget(1234, 0);
    if (msqid == -1)
        err::Exit("msgget");
    printf("msgget success, msqid=%d\n", msqid);

    int ret = msgctl(msqid, IPC_RMID, NULL);
    if (ret == -1)
        err::Exit("msgctl");

    return 0;
}
