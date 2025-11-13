#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 3

void* print_numbers(void* arg) {
    int thread_id = *(int*)arg;
    pthread_t system_tid = pthread_self();
    int i;

    for (i = 1; i <= 5; i++) {
        printf("Thread %d (TID: %lu): %d\n", thread_id, (unsigned long)system_tid, i);
    }

    printf("--- Thread %d finished ---\n", thread_id);
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];
    int i;
    int rc;

    printf("Main: Creating %d threads to print numbers...\n", NUM_THREADS);

    for (i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i;
        rc = pthread_create(&threads[i], NULL, print_numbers, (void*)&thread_ids[i]);
        if (rc) {
            fprintf(stderr, "ERROR; return code from pthread_create() is %d\n", rc);
            exit(EXIT_FAILURE);
        }
    }

    for (i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Main: All threads have completed. Exiting.\n");
    return 0;
}
