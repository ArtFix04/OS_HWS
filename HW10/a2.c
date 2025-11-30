#define _XOPEN_SOURCE 600
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

long long balance = 0;
pthread_mutex_t mtx;
pthread_spinlock_t spn;

int use_mutex = 1;
int long_wait = 0;

void* deposit(void* arg) {
    for (int i = 0; i < 1000; i++) {
        if (use_mutex) pthread_mutex_lock(&mtx);
        else pthread_spin_lock(&spn);

        balance++;
        if (long_wait) usleep(100);

        if (use_mutex) pthread_mutex_unlock(&mtx);
        else pthread_spin_unlock(&spn);
    }
    return NULL;
}

void* withdraw(void* arg) {
    for (int i = 0; i < 1000; i++) {
        if (use_mutex) pthread_mutex_lock(&mtx);
        else pthread_spin_lock(&spn);

        balance--;
        if (long_wait) usleep(100);

        if (use_mutex) pthread_mutex_unlock(&mtx);
        else pthread_spin_unlock(&spn);
    }
    return NULL;
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        printf("Usage: %s <mutex|spin> <short|long>\n", argv[0]);
        return 1;
    }

    use_mutex = (strcmp(argv[1], "mutex") == 0);
    long_wait = (strcmp(argv[2], "long") == 0);

    pthread_mutex_init(&mtx, NULL);
    pthread_spin_init(&spn, PTHREAD_PROCESS_PRIVATE);

    pthread_t t[8];
    clock_t start = clock();

    for (int i = 0; i < 4; i++) pthread_create(&t[i], NULL, deposit, NULL);
    for (int i = 4; i < 8; i++) pthread_create(&t[i], NULL, withdraw, NULL);

    for (int i = 0; i < 8; i++) pthread_join(t[i], NULL);

    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Balance: %lld\n", balance);
    printf("Time: %f\n", time_spent);

    pthread_mutex_destroy(&mtx);
    pthread_spin_destroy(&spn);

    return 0;
}
