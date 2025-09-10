#include <stdio.h>

int main(void) {
    int val = 500;
    int *ptr = &val;
    int **doublePtr = &ptr;

    printf("--- Assignment 4: Pointers to Pointers ---\n");
    printf("Value of val: %d\n", val);
    printf("Value using single pointer (*ptr): %d\n", *ptr);
    printf("Value using double pointer (**doublePtr): %d\n", **doublePtr);
    
    printf("\n--- Addresses ---\n");
    printf("Address of val (&val):             %p\n", (void *)&val);
    printf("Address stored in ptr (ptr):       %p\n", (void *)ptr);
    printf("Address of ptr (&ptr):             %p\n", (void *)&ptr);
    printf("Address stored in doublePtr (doublePtr): %p\n", (void *)doublePtr);

    return 0;
}
