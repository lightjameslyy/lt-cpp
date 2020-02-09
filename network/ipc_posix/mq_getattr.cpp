#include "lnp_lt.h"

using namespace lt;

int main(int argc, char* argv[]) {

    int mqid = mq_open("/abc", O_RDONLY);
    if (mqid == (mqd_t) -1)
        err::Exit("mq_open");

    printf("mq_open success\n");

    struct mq_attr attr;
    int ret = mq_getattr(mqid, &attr);
    if (ret == -1)
        err::Exit("mq_getattr");

    printf("max #msg=%ld\n", attr.mq_maxmsg);
    printf("max #bytes/msg=%ld\n", attr.mq_msgsize);
    printf("#currently on queue=%ld\n", attr.mq_curmsgs);

    ret = mq_close(mqid);
    if (ret == -1)
        err::Exit("mq_close");

    return 0;
}
