#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        fprintf(stderr, "Fork failed\n");
        return 1;
    }

    if (pid == 0) {
        printf("Child process (PID: %d) is running and will exit.\n", getpid());
        exit(0);
    }

    printf("Parent (PID: %d) created child (PID: %d).\n", getpid(), pid);

    sleep(20);

    printf("Parent is now waiting for the child to stop...\n");
    int status;
    wait(&status);
    printf("Parent has cleaned up the child process. No zombie!\n");

    sleep(20);

    return 0;
}
