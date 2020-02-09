#include "lnp_lt.h"

using namespace lt;

struct stu {
    char name[32];
    int age;
};

int main(int argc, char* argv[]) {

    int shmid = shmget(1234, 0, 0);
    if (shmid == -1)
        err::Exit("shmget");

    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}
