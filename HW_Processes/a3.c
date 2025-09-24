#include <stdio.h>
#include <stdlib.h>

void first_cleanup_task() {
    printf("First cleanup task is running!\n");
}

void second_cleanup_task() {
    printf("Second cleanup task is running!\n");
}

int main() {
    printf("Starting the main function.\n");

    atexit(first_cleanup_task);
    atexit(second_cleanup_task);

    printf("Registered the functions to run at exit.\n");
    printf("Main function is about to end.\n");

    return 0;
}
