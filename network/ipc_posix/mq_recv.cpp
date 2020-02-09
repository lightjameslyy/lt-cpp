#include "lnp_lt.h"

using namespace lt;

struct stu {
    char name[32];
    int age;
};

int main(int argc, char* argv[]) {

    int mqid = mq_open("/abc", O_RDONLY);
    if (mqid == (mqd_t) -1)
        err::Exit("mq_open");

    printf("mq_open success\n");

    struct mq_attr attr;
    int ret = mq_getattr(mqid, &attr);
    if (ret == -1)
        err::Exit("mq_getattr");

    stu s;
    unsigned prior;
    ret = mq_receive(mqid, (char*)&s, attr.mq_msgsize, &prior);
    if (ret == -1)
        err::Exit("mq_receive");

    printf("name=%s, age=%d, prior=%u\n", s.name, s.age, prior);

    ret = mq_close(mqid);
    if (ret == -1)
        err::Exit("mq_close");

    return 0;
}
