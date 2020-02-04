#include "lnp_lt.h"

using namespace lt;
using namespace lt::sem;

int semid;

static void print(char ch) {
    srand(getpid());
    for (int i = 0; i < 10 ; ++i) {
        sem_p(semid);
        printf("%c", ch);
        fflush(stdout);
        sleep(rand() % 3);
        printf("%c", ch);
        fflush(stdout);
        sem_v(semid);
        sleep(rand() % 2);
    }
}

int main(int argc, char* argv[]) {

    semid = sem_create(IPC_PRIVATE);
    sem_setval(semid, 0);

    pid_t pid = fork();
    if (pid == -1)
        err::Exit("fork");

    if (pid > 0) {
        sem_setval(semid, 1);
        print('O');
        wait(NULL);
        sem_rmid(semid);
    } else {
        print('X');
    }

    return 0;
}
