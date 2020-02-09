#include "lnp_lt.h"

using namespace lt;

struct stu {
    char name[32];
    int age;
};

int main(int argc, char* argv[]) {

    int shmid = shm_open("/xyz", O_CREAT | O_RDWR, 0666);
    if (shmid == -1)
        err::Exit("shm_open");

    printf("shm_open success\n");

    if (ftruncate(shmid, sizeof(stu)) == -1)
        err::Exit("ftruncate");

    struct stat buf;
    if (fstat(shmid, &buf) == -1)
        err::Exit("fstat");

    printf("size=%ld\n", buf.st_size);
    printf("mode=%o\n", buf.st_mode & 07777);

    close(shmid);

    return 0;
}
