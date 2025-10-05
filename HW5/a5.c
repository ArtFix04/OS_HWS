#include <stdio.h>
#include <stdlib.h>

int main() {
    int student_count, i;
    int *grades;
    int highest, lowest;

    printf("How many students are in the class? ");
    scanf("%d", &student_count);
    
    if (student_count <= 0) {
        printf("That doesn't seem like a valid number of students.\n");
        return 1;
    }

    grades = malloc(student_count * sizeof(int));
    if (grades == NULL) {
        printf("Couldn't get enough memory for the grades.\n");
        return 1;
    }

    printf("Please enter the %d grades now: ", student_count);
    for (i = 0; i < student_count; i++) {
        scanf("%d", &grades[i]);
    }

    highest = grades[0];
    lowest = grades[0];

    for (i = 1; i < student_count; i++) {
        if (grades[i] > highest) {
            highest = grades[i];
        }
        if (grades[i] < lowest) {
            lowest = grades[i];
        }
    }

    printf("The highest grade was: %d\n", highest);
    printf("The lowest grade was: %d\n", lowest);

    free(grades);

    return 0;
}
