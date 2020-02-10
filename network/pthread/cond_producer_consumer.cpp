#include "lnp_lt.h"

using namespace lt;

static const int CONSUMERS_COUNT = 2;
static const int PRODUCERS_COUNT = 4;

static pthread_mutex_t g_mutex;
static pthread_cond_t g_cond;

static pthread_t g_thread[CONSUMERS_COUNT + PRODUCERS_COUNT];

static int nReady = 0;

static void* consume(void* arg) {
    size_t thread_no = (size_t)arg;
    while(1) {
        pthread_mutex_lock(&g_mutex);
        while (nReady == 0) {
            printf("%lu begin wait a condition...\n", thread_no);
            pthread_cond_wait(&g_cond, &g_mutex);
        }
        printf("%lu end wait a condition...\n", thread_no);
        printf("%lu begin consume product...\n", thread_no);
        --nReady;
        printf("%lu end consume product...\n", thread_no);
        pthread_mutex_unlock(&g_mutex);
        sleep(1);
    }
    return NULL;
}

static void* produce(void* arg) {
    size_t thread_no = (size_t)arg;
    while(1) {
        pthread_mutex_lock(&g_mutex);
        printf("%lu begin produce product...\n", thread_no);
        ++nReady;
        printf("%lu end produce product...\n", thread_no);
        pthread_cond_signal(&g_cond);
        printf("%lu singnal\n", thread_no);
        pthread_mutex_unlock(&g_mutex);
        sleep(5);
    }
    return NULL;
}

int main(int argc, char* argv[]) {

    pthread_mutex_init(&g_mutex, NULL);
    pthread_cond_init(&g_cond, NULL);

    for (size_t i = 0; i < CONSUMERS_COUNT + PRODUCERS_COUNT; ++i) {
        if (i < CONSUMERS_COUNT) {
            pthread_create(&g_thread[i], NULL, consume, (void*)i);
            sleep(1);
        } else
            pthread_create(&g_thread[i], NULL, produce, (void*)i);
    }

    for (int i = 0; i < CONSUMERS_COUNT + PRODUCERS_COUNT; ++i)
        pthread_join(g_thread[i], NULL);

    pthread_mutex_destroy(&g_mutex);
    pthread_cond_destroy(&g_cond);

    return 0;
}
