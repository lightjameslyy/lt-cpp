#include "lnp_lt.h"

using namespace lt;

struct stu {
    char name[32];
    int age;
};

int main(int argc, char* argv[]) {

    int shmid = shm_open("/xyz", O_RDONLY, 0);
    if (shmid == -1)
        err::Exit("shm_open");

    printf("shm_open success\n");

    struct stat buf;
    if (fstat(shmid, &buf) == -1)
        err::Exit("fstat");
    printf("size=%ld\n", buf.st_size);
    printf("mode=%o\n", buf.st_mode & 07777);

    stu* p = (stu*)mmap(NULL, buf.st_size, PROT_READ, MAP_SHARED, shmid, 0);
    if (p == MAP_FAILED)
        err::Exit("mmap");

    printf("name=%s, age=%d\n", p->name, p->age);

    close(shmid);

    return 0;
}
