#include "lnp_lt.h"

using namespace lt;
using namespace lt::shm;

struct stu {
    char name[32];
    int age;
};

int main(int argc, char* argv[]) {

    shmfifo* fifo = shmfifo_init(1234, sizeof(stu), 5);

    stu s;
    memset(&s, 0, sizeof(s));
    for (int i = 0; i < 8; ++i) {
        shmfifo_get(fifo, &s);
        printf("name = %s, age = %d\n", s.name, s.age);
    }

    return 0;
}
