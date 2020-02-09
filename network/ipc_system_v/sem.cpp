#include "lnp_lt.h"

using namespace lt;
using namespace lt::sem;

int main(int argc, char* argv[]) {

    int semid = sem_create(1234);

    sleep(5);

    sem_rmid(semid);

    return 0;
}
