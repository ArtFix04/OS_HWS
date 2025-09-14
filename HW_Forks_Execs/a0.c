#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    printf("Main Process ID: %d\n", getpid());
    
    fork();
    fork();
    fork();
    
    printf("Process ID: %d, Parent ID: %d\n", getpid(), getppid());
    
    return 0;
}