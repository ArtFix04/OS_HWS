#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 3

void* thread_function(void* arg) {
    int thread_id = *(int*)arg;
    pthread_t system_tid = pthread_self();

    printf("Thread %d (System TID: %lu) is running.\n", thread_id, (unsigned long)system_tid);

    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];
    int i;
    int rc;

    printf("Main: Creating %d threads...\n", NUM_THREADS);

    for (i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i;
        rc = pthread_create(&threads[i], NULL, thread_function, (void*)&thread_ids[i]);

        if (rc) {
            fprintf(stderr, "ERROR; return code from pthread_create() is %d\n", rc);
            exit(EXIT_FAILURE);
        }
    }

    printf("Main: All threads created. Waiting for them to finish...\n");

    for (i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Main: All threads have completed. Exiting.\n");
    return 0;
}
