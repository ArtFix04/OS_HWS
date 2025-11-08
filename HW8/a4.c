#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

int main() {
    const char *filename = "log.txt";
    int fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd < 0) {
        perror("open (append)");
        return 1;
    }

    char line[1024];
    write(1, "Task 4: Enter log line: ", 24);
    ssize_t len = read(0, line, sizeof(line) - 1);
    if (len < 0) {
        perror("read (stdin)");
        close(fd);
        return 1;
    }

    char output[1100];
    pid_t pid = getpid();

    if (len > 0 && line[len - 1] == '\n') {
        line[len - 1] = '\0';
    } else {
        line[len] = '\0';
    }

    int out_len = sprintf(output, "PID=%d: %s\n", (int)pid, line);

    if (write(fd, output, out_len) != out_len) {
        perror("write (log)");
        close(fd);
        return 1;
    }

    off_t pos = lseek(fd, 0, SEEK_CUR);
    if (pos < 0) {
        perror("lseek(SEEK_CUR)");
    } else {
        printf("Task 4: New file offset: %ld\n", (long)pos);
    }
    close(fd);
    return 0;
}
