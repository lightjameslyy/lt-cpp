#include "lnp_lt.h"

using namespace lt;

struct stu {
    char name[32];
    int age;
};

int main(int argc, char* argv[]) {

    if (shm_unlink("/xyz") == -1)
        err::Exit("shm_unlink");

    return 0;
}
