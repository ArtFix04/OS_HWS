#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        fprintf(stderr, "Fork failed!\n");
        return 1;
    }

    if (pid == 0) {
        printf("Child Process: My PID is %d\n", getpid());
        exit(0);
    }

    printf("Parent Process: My PID is %d\n", getpid());
    printf("Parent process is finishing up.\n");

    return 0;
}
