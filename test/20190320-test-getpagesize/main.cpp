#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    printf("Get PAGESIZE via getpagesize(): %d\n", getpagesize());
    return 0;
}
