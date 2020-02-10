#include "lnp_lt.h"

using namespace lt;

struct tsd {
    pthread_t tid;
    char* str;
};

static pthread_key_t key_tsd;

static pthread_once_t once_control = PTHREAD_ONCE_INIT;

static void destroy_routine(void* value) {
    printf("destroy...\n");
    free(value);
}

static void once_routine(void) {
    pthread_key_create(&key_tsd, destroy_routine);
    printf("once routine: key init...\n");
}

static void* thread_routine(void* arg) {

    pthread_once(&once_control, once_routine);

    tsd* value = (tsd*)malloc(sizeof(tsd));
    value->tid = pthread_self();
    value->str = (char*)arg;
    pthread_setspecific(key_tsd, value);
    printf("%s setspecific %p\n", (char*)arg, value);

    value = (tsd*)pthread_getspecific(key_tsd);
    printf("%s getspecific: tid=0x%x, str=%s\n", (char*)arg, (int)value->tid, value->str);
    sleep(2);

    value = (tsd*)pthread_getspecific(key_tsd);
    printf("%s getspecific: tid=0x%x, str=%s\n", (char*)arg, (int)value->tid, value->str);

    return NULL;
}

int main(int argc, char* argv[]) {

    pthread_t tid1;
    pthread_t tid2;

    pthread_create(&tid1, NULL, thread_routine, (void*)"thread1");
    pthread_create(&tid2, NULL, thread_routine, (void*)"thread2");

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    pthread_key_delete(key_tsd);

    return 0;
}

