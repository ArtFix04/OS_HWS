#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, i;
    float sum = 0.0;
    int *arr;

    printf("Enter the number of elements you want to average: ");
    scanf("%d", &n);

    arr = calloc(n, sizeof(int));

    if (arr == NULL) {
        printf("Sorry, memory allocation failed.\n");
        return 1;
    }

    printf("The array is initially all zeroes: ");
    for (i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    printf("Now, enter your %d numbers: ", n);
    for (i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
        sum += arr[i];
    }

    printf("Here is your updated array: ");
    for (i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    printf("The average is: %.1f\n", sum / n);

    free(arr);

    return 0;
}

