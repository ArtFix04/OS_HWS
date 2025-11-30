#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t sA, sB, sC;
int n = 5;

void* runA(void* arg) {
    for (int i = 0; i < n; i++) {
        sem_wait(&sA);
        printf("Thread A: A %d\n", i);
        sem_post(&sB);
    }
    return NULL;
}

void* runB(void* arg) {
    for (int i = 0; i < n; i++) {
        sem_wait(&sB);
        printf("Thread B: B %d\n", i);
        sem_post(&sC);
    }
    return NULL;
}

void* runC(void* arg) {
    for (int i = 0; i < n; i++) {
        sem_wait(&sC);
        printf("Thread C: C %d\n", i);
        sem_post(&sA);
    }
    return NULL;
}

int main() {
    pthread_t t1, t2, t3;

    sem_init(&sA, 0, 1);
    sem_init(&sB, 0, 0);
    sem_init(&sC, 0, 0);

    pthread_create(&t1, NULL, runA, NULL);
    pthread_create(&t2, NULL, runB, NULL);
    pthread_create(&t3, NULL, runC, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    sem_destroy(&sA);
    sem_destroy(&sB);
    sem_destroy(&sC);

    return 0;
}
