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

    stu* p = (stu*)shmat(shmid, NULL, 0);
    if (p == (void*) -1)
        err::Exit("shmat");

    printf("name= %s, age= %d\n", p->name, p->age);

    shmdt(p);

    return 0;
}
