#include "lnp_lt.h"

using namespace lt;

struct stu {
    char name[32];
    int age;
};

int main(int argc, char* argv[]) {

    int shmid = shmget(1234, sizeof(stu), IPC_CREAT | 0666);
    if (shmid == -1)
        err::Exit("shmget");

    stu* p = (stu*)shmat(shmid, NULL, 0);
    if (p == (void*) -1)
        err::Exit("shmat");

    strcpy(p->name, "lightjames");
    p->age = 28;

    shmdt(p);

    return 0;
}
