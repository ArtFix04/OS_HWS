#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define JOBS 10
#define PRINTERS 3

sem_t pool;
int active = 0;
pthread_mutex_t mtx;

void* print_task(void* arg) {
    int id = *(int*)arg;

    printf("Thread %d waiting\n", id);
    sem_wait(&pool);

    pthread_mutex_lock(&mtx);
    active++;
    printf("Thread %d printing. Active: %d\n", id, active);
    pthread_mutex_unlock(&mtx);

    usleep(100000);

    pthread_mutex_lock(&mtx);
    active--;
    printf("Thread %d done. Active: %d\n", id, active);
    pthread_mutex_unlock(&mtx);

    sem_post(&pool);
    return NULL;
}

int main() {
    pthread_t t[JOBS];
    int ids[JOBS];

    sem_init(&pool, 0, PRINTERS);
    pthread_mutex_init(&mtx, NULL);

    for (int i = 0; i < JOBS; i++) {
        ids[i] = i + 1;
        pthread_create(&t[i], NULL, print_task, &ids[i]);
    }

    for (int i = 0; i < JOBS; i++) {
        pthread_join(t[i], NULL);
    }

    sem_destroy(&pool);
    pthread_mutex_destroy(&mtx);

    return 0;
}
