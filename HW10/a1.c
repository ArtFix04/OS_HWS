#define _XOPEN_SOURCE 600
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

long long counter = 0;
pthread_mutex_t lock;
pthread_spinlock_t spin;

int mode = 0; 
#define M_NONE 0
#define M_MUTEX 1
#define M_SPIN 2

#define N 4
#define M 1000000

void* count_func(void* arg) {
    for (int i = 0; i < M; i++) {
        if (mode == M_NONE) {
            counter++;
        } else if (mode == M_MUTEX) {
            pthread_mutex_lock(&lock);
            counter++;
            pthread_mutex_unlock(&lock);
        } else if (mode == M_SPIN) {
            pthread_spin_lock(&spin);
            counter++;
            pthread_spin_unlock(&spin);
        }
    }
    return NULL;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: %s <none|mutex|spin>\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "none") == 0) mode = M_NONE;
    else if (strcmp(argv[1], "mutex") == 0) mode = M_MUTEX;
    else if (strcmp(argv[1], "spin") == 0) mode = M_SPIN;
    else {
        printf("Unknown mode.\n");
        return 1;
    }

    pthread_mutex_init(&lock, NULL);
    pthread_spin_init(&spin, PTHREAD_PROCESS_PRIVATE);

    pthread_t t[N];
    for (int i = 0; i < N; i++) {
        pthread_create(&t[i], NULL, count_func, NULL);
    }

    for (int i = 0; i < N; i++) {
        pthread_join(t[i], NULL);
    }

    printf("Expected: %lld\n", (long long)N * M);
    printf("Actual:   %lld\n", counter);

    pthread_mutex_destroy(&lock);
    pthread_spin_destroy(&spin);

    return 0;
}
