#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define ARRAY_SIZE 10
int data_array[ARRAY_SIZE] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

typedef struct {
    int start_index;
    int end_index;
} ArrayPart;

void* sum_array_part(void* arg) {
    ArrayPart* part = (ArrayPart*)arg;
    int start = part->start_index;
    int end = part->end_index;
    long long partial_sum = 0;
    int i;

    pthread_t system_tid = pthread_self();

    for (i = start; i < end; i++) {
        partial_sum += data_array[i];
    }

    printf("Thread (TID: %lu): Summing from index %d to %d. Partial sum: %lld\n",
           (unsigned long)system_tid, start, end - 1, partial_sum);

    return NULL;
}

int main() {
    pthread_t threads[2];
    ArrayPart parts[2];
    int rc;

    int mid_point = ARRAY_SIZE / 2;

    parts[0].start_index = 0;
    parts[0].end_index = mid_point;

    parts[1].start_index = mid_point;
    parts[1].end_index = ARRAY_SIZE;

    printf("Main: Creating 2 threads to sum the array.\n");

    rc = pthread_create(&threads[0], NULL, sum_array_part, (void*)&parts[0]);
    if (rc) {
        fprintf(stderr, "ERROR; pthread_create() failed for thread 0\n");
        exit(EXIT_FAILURE);
    }

    rc = pthread_create(&threads[1], NULL, sum_array_part, (void*)&parts[1]);
    if (rc) {
        fprintf(stderr, "ERROR; pthread_create() failed for thread 1\n");
        exit(EXIT_FAILURE);
    }

    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);

    printf("Main: Both threads have finished.\n");
    return 0;
}
