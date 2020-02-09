#include "lnp_lt.h"

using namespace lt;

int main(int argc, char* argv[]) {

    int msqid = msgget(1234, 0666 | IPC_CREAT);   // 若不存在，创建
    //int msqid = msgget(1234, 0666 | IPC_CREAT | IPC_EXCL);  // 若不存在，创建；若已存在，报错
    //int msqid = msgget(IPC_PRIVATE, 0666);   // 总能创建成功，执行多次，key都为0，msqid不同
    //int msqid = msgget(1234, 0);   // 已存在，直接获取
    if (msqid == -1)
        err::Exit("msgget");

    printf("msgget success, msqid=%d\n", msqid);

    return 0;
}
