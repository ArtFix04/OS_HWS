#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

void report_child_status(pid_t pid, int status) {
    if (WIFEXITED(status)) {
        printf("Child %d finished normally. Its exit code was: %d\n", pid, WEXITSTATUS(status));
    } else {
        printf("Child %d terminated unexpectedly.\n", pid);
    }
}

int main() {
    pid_t child1, child2;

    child1 = fork();
    if (child1 == 0) {
        printf("Child 1 is running, will exit with code 5.\n");
        exit(5);
    }

    child2 = fork();
    if (child2 == 0) {
        printf("Child 2 is running, will exit with code 42.\n");
        exit(42);
    }

    printf("Parent is waiting for the children to finish.\n");

    int status1, status2;
    pid_t finished_pid1 = waitpid(child1, &status1, 0);
    report_child_status(finished_pid1, status1);

    pid_t finished_pid2 = waitpid(child2, &status2, 0);
    report_child_status(finished_pid2, status2);

    printf("Parent is all done.\n");

    return 0;
}
