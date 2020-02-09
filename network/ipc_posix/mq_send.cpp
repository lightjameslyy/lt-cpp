#include "lnp_lt.h"

using namespace lt;

struct stu {
    char name[32];
    int age;
};

int main(int argc, char* argv[]) {

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <prior>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int mqid = mq_open("/abc", O_WRONLY);
    if (mqid == (mqd_t) -1)
        err::Exit("mq_open");

    printf("mq_open success\n");

    stu s;
    strcpy(s.name, "test");
    s.age = 20;
    unsigned prior = atoi(argv[1]);
    int ret = mq_send(mqid, (const char*)&s, sizeof(s), prior);
    if (ret == -1)
        err::Exit("mq_send");

    ret = mq_close(mqid);
    if (ret == -1)
        err::Exit("mq_close");

    return 0;
}
