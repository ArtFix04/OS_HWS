#include <stdio.h>

int main(void) {
    int arr[5] = {10, 20, 30, 40, 50};
    int *ptr = arr;
    int i;

    printf("--- Assignment 2: Pointer Arithmetic ---\n");
    printf("Printing original array using a pointer:\n");
    for (i = 0; i < 5; ++i) {
        printf("Element %d: %d\n", i, *(ptr + i));
    }
    
    printf("\nModifying array values (adding 5 to each)...\n");
    for (i = 0; i < 5; ++i) {
        *(ptr + i) += 5;
    }
    
    printf("\nPrinting modified array using a pointer:\n");
    for (i = 0; i < 5; ++i) {
        printf("Element %d: %d\n", i, *ptr++);
    }

    ptr = arr; 

    printf("\nPrinting modified array using the array name:\n");
    for (i = 0; i < 5; ++i) {
        printf("Element %d: %d\n", i, arr[i]);
    }
    
    return 0;
}
