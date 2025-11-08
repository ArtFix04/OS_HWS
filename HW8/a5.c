#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

int main() {
    const char *filename = "sparse.bin";
    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror("open (sparse)");
        return 1;
    }

    printf("Task 5: Writing 'START' to '%s'\n", filename);
    if (write(fd, "START", 5) != 5) {
        perror("write (start)");
        close(fd);
        return 1;
    }

    long offset = 1024 * 1024;
    printf("Task 5: Seeking forward by %ld bytes...\n", offset);
    if (lseek(fd, offset, SEEK_CUR) < 0) {
        perror("lseek");
        close(fd);
        return 1;
    }

    printf("Task 5: Writing 'END'\n");
    if (write(fd, "END", 3) != 3) {
        perror("write (end)");
        close(fd);
        return 1;
    }
    close(fd);

    printf("Task 5: Reopening to check size...\n");
    fd = open(filename, O_RDONLY);
    if (fd < 0) {
        perror("open (read sparse)");
        return 1;
    }

    off_t size = lseek(fd, 0, SEEK_END);
    printf("Task 5: Apparent file size: %ld bytes\n", (long)size);
    close(fd);
    return 0;
}

