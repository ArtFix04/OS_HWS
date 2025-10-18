#include <stdio.h>
#include <stddef.h>

struct NormalStruct {
    char a;
    int b;
    double c;
};

#pragma pack(push, 1)
struct PackedStruct {
    char a;
    int b;
    double c;
};
#pragma pack(pop) 

#pragma pack(push, 2)
struct PackedStruct2 {
    char a;
    int b;
    double c;
};
#pragma pack(pop)


int main() {
    printf("--- Normal Struct (Default Alignment) ---\n");
    printf("Total size: %zu bytes\n", sizeof(struct NormalStruct));
    printf("Offset of a: %zu\n", offsetof(struct NormalStruct, a));
    printf("Offset of b: %zu\n", offsetof(struct NormalStruct, b));
    printf("Offset of c: %zu\n", offsetof(struct NormalStruct, c));

    printf("\n--- Packed Struct #pragma pack(1) ---\n");
    printf("Total size: %zu bytes\n", sizeof(struct PackedStruct));
    printf("Offset of a: %zu\n", offsetof(struct PackedStruct, a));
    printf("Offset of b: %zu\n", offsetof(struct PackedStruct, b));
    printf("Offset of c: %zu\n", offsetof(struct PackedStruct, c));

    printf("\n--- Bonus: Packed Struct #pragma pack(2) ---\n");
    printf("Total size: %zu bytes\n", sizeof(struct PackedStruct2));
    printf("Offset of a: %zu\n", offsetof(struct PackedStruct2, a));
    printf("Offset of b: %zu\n", offsetof(struct PackedStruct2, b));
    printf("Offset of c: %zu\n", offsetof(struct PackedStruct2, c));

    return 0;
}
