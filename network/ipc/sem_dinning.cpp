#include "lnp_lt.h"

using namespace lt;
using namespace lt::sem;

static int semid;

static void wait_for_2fork(int id) {
    int left = id;
    int right = (id + 1) % 5;
    struct sembuf sops[2] =  {
        {left, -1, 0},
        {right, -1, 0},
    };
    semop(semid, sops, 2);
}

static void free_2fork(int id) {
    int left = id;
    int right = (id + 1) % 5;
    struct sembuf sops[2] =  {
        {left, 1, 0},
        {right, 1, 0},
    };
    semop(semid, sops, 2);
}

static void philosopher(int id) {
    srand(id);
    for (;;) {
        printf("%d is thinking...\n", id);
        sleep(rand() % 5 + 1);
        printf("%d is hungry...\n", id);
        wait_for_2fork(id);
        printf("%d is eating...\n", id);
        sleep(rand() % 5 + 1);
        free_2fork(id);
    }
}

static void philosopher_deadlock(int id) {
    srand(id);
    int left = id;
    int right = (id + 1) % 5;
    for (;;) {
        printf("%d is thinking...\n", id);
        sleep(rand() % 5 + 1);
        printf("%d is hungry...\n", id);
        sem_p(semid, left);
        sleep(rand() % 5 + 1);
        sem_p(semid, right);
        printf("%d is eating...\n", id);
        sleep(rand() % 5 + 1);
        sem_v(semid, left);
        sleep(rand() % 5 + 1);
        sem_v(semid, right);
    }
}

int main(int argc, char* argv[]) {

    semid = semget(IPC_PRIVATE, 5, IPC_CREAT | 0666);
    if (semid == -1)
        err::Exit("semget");

    semun su;
    su.val = 1;
    for (int i = 0; i < 5; ++i) {
        semctl(semid, i, SETVAL, su);
    }

    int id = 0;
    pid_t pid;
    for (int i = 1; i < 5; ++i) {
        pid = fork();
        if (pid == -1)
            err::Exit("fork");
        if (pid == 0) {
            id = i;
            break;
        }
    }

    //philosopher(id);
    philosopher_deadlock(id);

    return 0;
}
