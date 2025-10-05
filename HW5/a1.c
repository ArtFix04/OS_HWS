#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, i, sum = 0;
    int *arr;

    printf("How many numbers would you like to sum? ");
    scanf("%d", &n);

    arr = malloc(n * sizeof(int));

    if (arr == NULL) {
        printf("Error: Memory could not be allocated.\n");
        return 1;
    }

    printf("Please enter the %d numbers: ", n);
    for (i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
        sum += arr[i];
    }

    printf("The sum of the numbers is: %d\n", sum);

    free(arr);

    return 0;
}
