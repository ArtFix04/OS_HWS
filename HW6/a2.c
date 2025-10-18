#include <stdio.h>
#include <stddef.h> 

struct Unoptimized {
    char a;
    int b;
    double c;
};

struct Optimized {
    double c;
    int b;
    char a;
};

struct WorstCase {
    char a;
    double c;
    int b;
};


int main() {
    printf("--- Unoptimized Struct (char, int, double) ---\n");
    printf("Total size: %zu bytes\n", sizeof(struct Unoptimized));
    printf("Offset of a: %zu\n", offsetof(struct Unoptimized, a));
    printf("Offset of b: %zu\n", offsetof(struct Unoptimized, b));
    printf("Offset of c: %zu\n", offsetof(struct Unoptimized, c));

    printf("\n--- Optimized Struct (double, int, char) ---\n");
    printf("Total size: %zu bytes\n", sizeof(struct Optimized));
    printf("Offset of c: %zu\n", offsetof(struct Optimized, c));
    printf("Offset of b: %zu\n", offsetof(struct Optimized, b));
    printf("Offset of a: %zu\n", offsetof(struct Optimized, a));

    printf("\n--- Worst-Case Struct (char, double, int) ---\n");
    printf("Total size: %zu bytes\n", sizeof(struct WorstCase));
    printf("Offset of a: %zu\n", offsetof(struct WorstCase, a));
    printf("Offset of c: %zu\n", offsetof(struct WorstCase, c));
    printf("Offset of b: %zu\n", offsetof(struct WorstCase, b));

    return 0;
}
