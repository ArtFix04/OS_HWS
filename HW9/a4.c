#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int numbers[] = {1, 2, 3, 4, 5};
#define ARRAY_SIZE (sizeof(numbers) / sizeof(numbers[0]))

void* calculate_square(void* arg) {
    int number = *(int*)arg;
    long long square = (long long)number * number;
    pthread_t system_tid = pthread_self();

    printf("Thread (TID: %lu): Square of %d is %lld\n", 
           (unsigned long)system_tid, number, square);

    return NULL;
}

int main() {
    pthread_t threads[ARRAY_SIZE];
    int i;
    int rc;

    printf("Main: Creating %d threads to calculate squares...\n", (int)ARRAY_SIZE);

    for (i = 0; i < ARRAY_SIZE; i++) {
        rc = pthread_create(&threads[i], NULL, calculate_square, (void*)&numbers[i]);
        if (rc) {
            fprintf(stderr, "ERROR; return code from pthread_create() is %d\n", rc);
            exit(EXIT_FAILURE);
        }
    }

    for (i = 0; i < ARRAY_SIZE; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Main: All square calculations are complete. Exiting.\n");
    return 0;
}
