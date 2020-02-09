#include "lnp_lt.h"

using namespace lt;

struct stu {
    char name[4];
    int age;
};

int main(int argc, char* argv[]) {

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int fd = open(argv[1], O_RDWR, 0666);
    if (fd == -1)
        err::Exit("open");

    stu* p = (stu*)mmap(NULL, sizeof(stu) * 5, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (p == NULL)
        err::Exit("mmap");

    for (int i = 0; i < 5; ++i) {
        printf("name= %s, age = %d\n", p[i].name, p[i].age);
    }

    munmap(p, sizeof(stu) * 5);

    printf("exit ...\n");

    return 0;
}
