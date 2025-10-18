#include <stdio.h>

int main() {
    int i;
    char c;
    double d;
    short s;

    printf("--- Data Type Sizes ---\n");
    printf("Size of char:   %zu byte\n", sizeof(c));
    printf("Size of short:  %zu bytes\n", sizeof(s));
    printf("Size of int:    %zu bytes\n", sizeof(i));
    printf("Size of double: %zu bytes\n", sizeof(d));

    printf("\n--- Variable Memory Addresses ---\n");
    printf("Address of char:   %p\n", (void*)&c);
    printf("Address of short:  %p\n", (void*)&s);
    printf("Address of int:    %p\n", (void*)&i);
    printf("Address of double: %p\n", (void*)&d);

    return 0;
}
