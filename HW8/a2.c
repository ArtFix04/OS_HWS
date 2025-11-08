#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

int main() {
    const char *filename = "data.txt";
    const char *data = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int fd;
    off_t size;

    printf("Task 2: Writing 26 bytes to '%s'\n", filename);
    fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror("open (write)");
        return 1;
    }

    if (write(fd, data, strlen(data)) != strlen(data)) {
        perror("write");
        close(fd);
        return 1;
    }
    close(fd);

    printf("Task 2: Reopening with O_RDWR\n");
    fd = open(filename, O_RDWR);
    if (fd < 0) {
        perror("open (read/write)");
        return 1;
    }

    size = lseek(fd, 0, SEEK_END);
    printf("Task 2: Original size via lseek: %ld bytes\n", (long)size);

    printf("Task 2: Truncating file to 10 bytes...\n");
    if (ftruncate(fd, 10) < 0) {
        perror("ftruncate");
        close(fd);
        return 1;
    }

    size = lseek(fd, 0, SEEK_END);
    printf("Task 2: New size via lseek: %ld bytes\n", (long)size);

    lseek(fd, 0, SEEK_SET);

    char buffer[11];
    ssize_t bytes_read = read(fd, buffer, 10);
    if (bytes_read < 0) {
        perror("read");
    } else {
        buffer[bytes_read] = '\0';
        printf("Task 2: Content after truncate: '%s'\n", buffer);
    }
    close(fd);
    return 0;
}
