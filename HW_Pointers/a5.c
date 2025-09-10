#include <stdio.h>

int main(void) {
    char str[] = "Hello";
    char *ptr = str;
    char *tempPtr;
    int count;

    printf("--- Assignment 5: Strings and Character Pointers ---\n");
    
    printf("Printing string using a pointer loop: ");
    tempPtr = ptr;
    while (*tempPtr != '\0') {
        printf("%c", *tempPtr);
        tempPtr++;
    }
    printf("\n");
    
    count = 0;
    tempPtr = ptr;
    while (*tempPtr != '\0') {
        count++;
        tempPtr++;
    }
    
    printf("Number of characters counted with pointer: %d\n", count);
    printf("Printing string directly using printf: %s\n", ptr);
    
    return 0;
}
