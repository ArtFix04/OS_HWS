#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }

    if (pid == 0) {
        printf("--- Child Process (echo output) ---\n");
        execl("/bin/echo", "echo", "Hello from the child process", NULL);
        perror("execl failed");
        exit(1);
    } else {
        wait(NULL);
        printf("--- Parent Process ---\n");
        printf("Parent process done\n");
    }

    return 0;
}