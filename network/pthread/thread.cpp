#include "lnp_lt.h"

using namespace lt;

static void* thread_routine(void* arg) {
    for (int i = 0; i < 20; ++i) {
        printf("B");
        fflush(stdout);
        /*
        if (i == 3)
            pthread_exit((void*)"ABC");
        */
        usleep(20);
    }
    return (void*)"DEF";
}

int main(int argc, char* argv[]) {

    pthread_t tid;
    int ret = pthread_create(&tid, NULL, thread_routine, NULL);
    if (ret != 0) {
        fprintf(stderr, "pthread_create:%s\n", strerror(ret));
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < 20; ++i) {
        printf("A");
        fflush(stdout);
        usleep(20);
    }

    void* value;
    ret = pthread_join(tid, &value);
    if (ret != 0) {
        fprintf(stderr, "pthread_join:%s\n", strerror(ret));
        exit(EXIT_FAILURE);
    }
    printf("\n");

    printf("return message: %s\n", (char*)value);

    return 0;
}
