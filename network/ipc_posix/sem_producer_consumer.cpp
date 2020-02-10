#include "lnp_lt.h"

using namespace lt;

static const int CONSUMERS_COUNT = 1;
static const int PRODUCERS_COUNT = 5;
static const int BUFSIZE = 10;

static int g_buf[BUFSIZE];
static unsigned int in = 0;
static unsigned int out = 0;
static unsigned int produce_id = 0;
static unsigned int consume_id = 0;

sem_t g_sem_full;
sem_t g_sem_empty;
pthread_mutex_t g_mutex;

pthread_t g_thread[CONSUMERS_COUNT + PRODUCERS_COUNT];

static void* consume(void* arg) {
    size_t thread_no = (size_t)arg;
    while(1) {
        printf("%lu wait buffer not empty\n", thread_no);
        sem_wait(&g_sem_empty);
        pthread_mutex_lock(&g_mutex);

        for (int i = 0; i < BUFSIZE; ++i) {
            printf("%02d ", i);
            if (g_buf[i] == -1)
                printf("null");
            else
                printf("%d", g_buf[i]);
            if (i == out)
                printf("\t<--consume");
            printf("\n");
        }

        consume_id = g_buf[out];
        printf("%lu begin consuming product %d\n", thread_no, consume_id);
        g_buf[out] = -1;
        out = (out + 1) % BUFSIZE;
        printf("%lu end consuming product %d\n", thread_no, consume_id);

        pthread_mutex_unlock(&g_mutex);
        sem_post(&g_sem_full);
        sleep(1);
    }
    return NULL;
}

static void* produce(void* arg) {
    size_t thread_no = (size_t)arg;
    while(1) {
        printf("%lu wait buffer not full\n", thread_no);
        sem_wait(&g_sem_full);
        pthread_mutex_lock(&g_mutex);

        for (int i = 0; i < BUFSIZE; ++i) {
            printf("%02d ", i);
            if (g_buf[i] == -1)
                printf("null");
            else
                printf("%d", g_buf[i]);
            if (i == in)
                printf("\t<--produce");
            printf("\n");
        }

        printf("%lu begin producing product %d\n", thread_no, produce_id);
        g_buf[in] = produce_id;
        in = (in + 1) % BUFSIZE;
        printf("%lu end producing product %d\n", thread_no, produce_id++);

        pthread_mutex_unlock(&g_mutex);
        sem_post(&g_sem_empty);
        sleep(5);
    }
    return NULL;
}

int main(int argc, char* argv[]) {

    for (int i = 0; i < BUFSIZE; ++i)
        g_buf[i] = -1;

    sem_init(&g_sem_full, 0, BUFSIZE);
    sem_init(&g_sem_empty, 0, 0);

    pthread_mutex_init(&g_mutex, NULL);

    for (size_t i = 0; i < CONSUMERS_COUNT + PRODUCERS_COUNT; ++i) {
        if (i < CONSUMERS_COUNT)
            pthread_create(&g_thread[i], NULL, consume, (void*)i);
        else
            pthread_create(&g_thread[i], NULL, produce, (void*)i);
    }

    for (int i = 0; i < CONSUMERS_COUNT + PRODUCERS_COUNT; ++i)
        pthread_join(g_thread[i], NULL);

    sem_destroy(&g_sem_full);
    sem_destroy(&g_sem_empty);
    pthread_mutex_destroy(&g_mutex);

    return 0;
}
