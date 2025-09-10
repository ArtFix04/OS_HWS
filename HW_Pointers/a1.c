#include <stdio.h>

int main(void) {
    int num = 42;
    int *ptr = &num;

    printf("--- Assignment 1: Basics of Pointers ---\n");
    printf("Value of num: %d\n", num);
    printf("Address of num (using &num): %p\n", (void *)&num);
    printf("Address of num (using ptr): %p\n", (void *)ptr);
    printf("Value of num (using *ptr): %d\n", *ptr);
    
    printf("\nModifying value using the pointer...\n");
    *ptr = 100;

    printf("New value of num: %d\n", num);
    printf("New value pointed to by ptr (*ptr): %d\n", *ptr);

    return 0;
}
