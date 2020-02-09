#include "lnp_lt.h"

using namespace lt;

static int mqid;
static struct mq_attr attr;
static struct sigevent sigev;

struct stu {
    char name[32];
    int age;
};

static void sigusr1_handler(int sig) {
    int ret = mq_notify(mqid, &sigev);
    if (ret == -1)
        err::Exit("mq_notify");
    stu s;
    unsigned prior;
    ret = mq_receive(mqid, (char*)&s, attr.mq_msgsize, &prior);
    if (ret == -1)
        err::Exit("mq_receive");

    printf("name=%s, age=%d, prior=%u\n", s.name, s.age, prior);

}

int main(int argc, char* argv[]) {
    mqid = mq_open("/abc", O_RDONLY);
    if (mqid == (mqd_t) -1)
        err::Exit("mq_open");

    printf("mq_open success\n");

    int ret = mq_getattr(mqid, &attr);
    if (ret == -1)
        err::Exit("mq_getattr");

    signal(SIGUSR1, sigusr1_handler);

    sigev.sigev_notify = SIGEV_SIGNAL;
    sigev.sigev_signo = SIGUSR1;
    ret = mq_notify(mqid, &sigev);
    if (ret == -1)
        err::Exit("mq_notify");

    while(1)
        pause();

    ret = mq_close(mqid);
    if (ret == -1)
        err::Exit("mq_close");

    return 0;
}
