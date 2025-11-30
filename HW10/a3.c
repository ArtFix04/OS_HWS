#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define SIZE 8
#define P 2
#define C 2
#define ITEMS 10

int buffer[SIZE];
int in = 0;
int out = 0;

sem_t empty;
sem_t full;
pthread_mutex_t mtx;

void* producer(void* arg) {
    int id = *(int*)arg;
    for (int i = 0; i < ITEMS; i++) {
        int val = id * 1000 + i;
        
        sem_wait(&empty);
        pthread_mutex_lock(&mtx);

        buffer[in] = val;
        printf("Prod %d wrote %d at %d\n", id, val, in);
        in = (in + 1) % SIZE;

        pthread_mutex_unlock(&mtx);
        sem_post(&full);
    }
    return NULL;
}

void* consumer(void* arg) {
    int id = *(int*)arg;
    int consumed = 0;
    while (consumed < ITEMS) {
        sem_wait(&full);
        pthread_mutex_lock(&mtx);

        int val = buffer[out];
        printf("Cons %d read %d from %d\n", id, val, out);
        out = (out + 1) % SIZE;

        pthread_mutex_unlock(&mtx);
        sem_post(&empty);
        consumed++;
    }
    return NULL;
}

int main() {
    pthread_t p[P], c[C];
    int p_ids[P], c_ids[C];

    sem_init(&empty, 0, SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mtx, NULL);

    for (int i = 0; i < P; i++) {
        p_ids[i] = i + 1;
        pthread_create(&p[i], NULL, producer, &p_ids[i]);
    }

    for (int i = 0; i < C; i++) {
        c_ids[i] = i + 1;
        pthread_create(&c[i], NULL, consumer, &c_ids[i]);
    }

    for (int i = 0; i < P; i++) pthread_join(p[i], NULL);
    for (int i = 0; i < C; i++) pthread_join(c[i], NULL);

    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mtx);

    return 0;
}
