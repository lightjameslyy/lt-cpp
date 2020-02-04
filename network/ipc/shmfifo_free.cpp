#include "lnp_lt.h"

using namespace lt;
using namespace lt::shm;

struct stu {
    char name[32];
    int age;
};

int main(int argc, char* argv[]) {

    shmfifo* fifo = shmfifo_init(1234, sizeof(stu), 5);

    shmfifo_destroy(fifo);

    return 0;
}
