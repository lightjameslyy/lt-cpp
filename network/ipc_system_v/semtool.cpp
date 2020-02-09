#include "lnp_lt.h"

using namespace lt;

union semun {
    int              val;    /* Value for SETVAL */
    struct semid_ds* buf;    /* Buffer for IPC_STAT, IPC_SET */
    unsigned short*  array;  /* Array for GETALL, SETALL */
    struct seminfo*  __buf;  /* Buffer for IPC_INFO (Linux-specific) */
};

static int sem_create(key_t key) {
    int semid = semget(key, 1, IPC_CREAT | IPC_EXCL | 0666);
    if (semid == -1)
        err::Exit("semget");

    return semid;
}

static int sem_open(key_t key) {
    int semid = semget(key, 0, 0);
    if (semid == -1)
        err::Exit("semget");

    return semid;
}

static int sem_setval(int semid, int val) {
    semun su;
    su.val = val;
    int ret = semctl(semid, 0, SETVAL, su);
    if (ret == -1)
        err::Exit("sem_setval");
    return ret;
}

static int sem_getval(int semid) {
    int ret = semctl(semid, 0, GETVAL, 0);
    if (ret == -1)
        err::Exit("sem_getval");
    printf("current value: %d\n", ret);
    return ret;
}

static int sem_rmid(int semid) {
    int ret = semctl(semid, 0, IPC_RMID, 0);
    if (ret == -1)
        err::Exit("sem_rmid");
    return ret;
}

static int sem_p(int semid) {
    struct sembuf sops = {0, -1, 0};
    int ret = semop(semid, &sops, 1);
    if (ret == -1)
        err::Exit("semop");
    return ret;
}

static int sem_v(int semid) {
    struct sembuf sops = {0, 1, 0};
    int ret = semop(semid, &sops, 1);
    if (ret == -1)
        err::Exit("semop");
    return ret;
}

static int sem_getmode(int semid) {
    semun su;
    struct semid_ds sem;
    su.buf = &sem;
    int ret = semctl(semid, 0, IPC_STAT, su);
    if (ret == -1)
        err::Exit("semctl");

    printf("current permissions is %o\n", su.buf->sem_perm.mode);
    return ret;
}

static int sem_setmode(int semid, char* mode) {
    semun su;
    struct semid_ds sem;
    su.buf = &sem;
    int ret = semctl(semid, 0, IPC_STAT, su);
    if (ret == -1)
        err::Exit("semctl");

    printf("current permissions is %o\n", su.buf->sem_perm.mode);
    sscanf(mode, "%o", (unsigned int*)&su.buf->sem_perm.mode);
    ret = semctl(semid, 0, IPC_SET, su);
    if (ret == -1)
        err::Exit("semctl");

    printf("permissions updated...\n");

    return ret;
}

static void usage() {
    fprintf(stderr, "usage:\n");
    fprintf(stderr, "semtool -c\n");
    fprintf(stderr, "semtool -d\n");
    fprintf(stderr, "semtool -p\n");
    fprintf(stderr, "semtool -v\n");
    fprintf(stderr, "semtool -s <val>\n");
    fprintf(stderr, "semtool -g\n");
    fprintf(stderr, "semtool -f\n");
    fprintf(stderr, "semtool -m <mode>\n");
}

int main(int argc, char* argv[]) {

    int opt = getopt(argc, argv, "cdpvs:gfm:");
    if (opt == '?')
        exit(EXIT_FAILURE);

    if (opt == -1) {
        usage();
        exit(EXIT_FAILURE);
    }

    key_t key = ftok(".", 's');
    int semid;
    switch(opt) {
    case 'c':
        sem_create(key);
        break;
    case 'p':
        semid = sem_open(key);
        sem_p(semid);
        sem_getval(semid);
        break;
    case 'v':
        semid = sem_open(key);
        sem_v(semid);
        sem_getval(semid);
        break;
    case 'd':
        semid = sem_open(key);
        sem_rmid(semid);
        break;
    case 's':
        semid = sem_open(key);
        sem_setval(semid, atoi(optarg));
        break;
    case 'g':
        semid = sem_open(key);
        sem_getval(semid);
        break;
    case 'f':
        semid = sem_open(key);
        sem_getmode(semid);
        break;
    case 'm':
        semid = sem_open(key);
        sem_setmode(semid, argv[2]);
        break;
    }

    return 0;
}
