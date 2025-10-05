#include <stdio.h>
#include <stdlib.h>

int main() {
    int i;
    int *arr;

    arr = malloc(10 * sizeof(int));

    if (arr == NULL) {
        printf("Failed to allocate memory.\n");
        return 1;
    }

    printf("Enter 10 integers, please: ");
    for (i = 0; i < 10; i++) {
        scanf("%d", &arr[i]);
    }

    int *temp_arr = realloc(arr, 5 * sizeof(int));
    
    if (temp_arr == NULL) {
        printf("Oops, couldn't resize the memory.\n");
        free(arr);
        return 1;
    }
    arr = temp_arr;

    printf("After resizing, we're keeping the first 5: ");
    for (i = 0; i < 5; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    free(arr);

    return 0;
}

