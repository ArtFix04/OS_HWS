#include <stdio.h>
#include <stdlib.h>

#define MAX_STRING_LEN 51

int main() {
    int i;
    char **strings;

    strings = malloc(3 * sizeof(char*));
    if (!strings) {
        printf("Failed to allocate memory for string array.\n");
        return 1;
    }

    printf("Please enter 3 strings: ");
    for (i = 0; i < 3; i++) {
        strings[i] = malloc(MAX_STRING_LEN * sizeof(char));
        if (!strings[i]) {
            printf("Failed to allocate memory for a string.\n");
            return 1;
        }
        scanf("%50s", strings[i]);
    }

    char **temp = realloc(strings, 5 * sizeof(char*));
    if (!temp) {
        printf("Failed to resize the string array.\n");
        return 1;
    }
    strings = temp;

    printf("Great, now enter 2 more strings: ");
    for (i = 3; i < 5; i++) {
        strings[i] = malloc(MAX_STRING_LEN * sizeof(char));
        if (!strings[i]) {
            printf("Failed to allocate memory for a new string.\n");
            return 1;
        }
        scanf("%50s", strings[i]);
    }

    printf("Here are all the strings you entered: ");
    for (i = 0; i < 5; i++) {
        printf("%s ", strings[i]);
    }
    printf("\n");

    for (i = 0; i < 5; i++) {
        free(strings[i]);
    }
    free(strings);

    return 0;
}

