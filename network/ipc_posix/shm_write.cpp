#include "lnp_lt.h"

using namespace lt;

struct stu {
    char name[32];
    int age;
};

int main(int argc, char* argv[]) {

    int shmid = shm_open("/xyz", O_RDWR, 0);
    if (shmid == -1)
        err::Exit("shm_open");

    printf("shm_open success\n");

    struct stat buf;
    if (fstat(shmid, &buf) == -1)
        err::Exit("fstat");
    printf("size=%ld\n", buf.st_size);
    printf("mode=%o\n", buf.st_mode & 07777);

    stu* p = (stu*)mmap(NULL, buf.st_size, PROT_WRITE, MAP_SHARED, shmid, 0);
    if (p == MAP_FAILED)
        err::Exit("mmap");

    strcpy(p->name, "test");
    p->age = 20;

    close(shmid);

    return 0;
}
