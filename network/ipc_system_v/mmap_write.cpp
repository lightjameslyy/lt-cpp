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

    int fd = open(argv[1], O_CREAT | O_RDWR | O_TRUNC, 0666);
    if (fd == -1)
        err::Exit("open");

    lseek(fd, sizeof(stu) * 5 - 1, SEEK_SET);

    write(fd, "", 1);

    stu* p = (stu*)mmap(NULL, sizeof(stu) * 5, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (p == NULL)
        err::Exit("mmap");

    char ch = 'a';
    for (int i = 0; i < 5; ++i) {
        memcpy(p[i].name, &ch, 1);
        p[i].age = 20 + i;
        ch++;
    }

    printf("initialized\n");

    munmap(p, sizeof(stu) * 5);

    printf("exit ...\n");

    return 0;
}
