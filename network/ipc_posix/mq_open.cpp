#include "lnp_lt.h"

using namespace lt;

int main(int argc, char* argv[]) {

    int mqid = mq_open("/abc", O_CREAT | O_RDWR, 0666, NULL);
    if (mqid == (mqd_t) -1)
        err::Exit("mq_open");

    printf("mq_open success\n");

    int ret = mq_close(mqid);
    if (ret == -1)
        err::Exit("mq_close");

    return 0;
}
