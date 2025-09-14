#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t pid1 = fork();

    if (pid1 < 0) {
        perror("fork1 failed");
        exit(1);
    }

    if (pid1 == 0) {
        printf("--- Child 1 (ls output) ---\n");
        execl("/bin/ls", "ls", "-l", NULL);
        perror("execl failed");
        exit(1);
    } 
    
    pid_t pid2 = fork();
    
    if (pid2 < 0) {
        perror("fork2 failed");
        exit(1);
    }

    if (pid2 == 0) {
        printf("--- Child 2 (date output) ---\n");
        execl("/bin/date", "date", NULL);
        perror("execl failed");
        exit(1);
    }

    wait(NULL);
    wait(NULL);
    printf("--- Parent Process ---\n");
    printf("Parent process done\n");
    
    return 0;
}