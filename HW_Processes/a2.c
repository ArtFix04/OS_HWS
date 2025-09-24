#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main() {
    pid_t child1_pid, child2_pid;
    int status;

    child1_pid = fork();
    if (child1_pid == 0) {
        printf("Child 1 (PID %d) is doing some work.\n", getpid());
        sleep(2);
        printf("Child 1 is done.\n");
        exit(10);
    }
    printf("Parent created child 1 with PID %d\n", child1_pid);

    child2_pid = fork();
    if (child2_pid == 0) {
        printf("Child 2 (PID %d) is doing some work.\n", getpid());
        sleep(4);
        printf("Child 2 is done.\n");
        exit(20);
    }
    printf("Parent created child 2 with PID %d\n", child2_pid);

    printf("Parent is waiting for Child 2 to finish first.\n");
    waitpid(child2_pid, &status, 0);
    if (WIFEXITED(status)) {
        printf("Child 2 finished with status: %d\n", WEXITSTATUS(status));
    }

    printf("Parent is now waiting for Child 1.\n");
    wait(&status);
    if (WIFEXITED(status)) {
        printf("Child 1 finished with status: %d\n", WEXITSTATUS(status));
    }

    printf("Parent process has finished.\n");

    return 0;
}
