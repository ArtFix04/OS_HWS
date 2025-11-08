#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

ssize_t read_line(int fd, char *buffer, size_t max_len) {
    ssize_t len = read(fd, buffer, max_len - 1);
    if (len > 0) {
        if (buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
            return len - 1;
        }
        buffer[len] = '\0';
    }
    return len;
}

int main() {
    char path[256];
    write(1, "Task 3: Enter file to reverse: ", 31);
    read_line(0, path, sizeof(path));

    int fd = open(path, O_RDONLY);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    off_t size = lseek(fd, 0, SEEK_END);
    if (size < 0) {
        perror("lseek(SEEK_END)");
        close(fd);
        return 1;
    }

    printf("Task 3: Reversing %ld bytes from '%s':\n", (long)size, path);
    char byte_buf;
    for (off_t i = size - 1; i >= 0; i--) {
        if (lseek(fd, i, SEEK_SET) < 0) {
            perror("lseek(SEEK_SET)");
            break;
        }
        if (read(fd, &byte_buf, 1) != 1) {
            if (size > 0) perror("read"); // Avoid error on 0-byte file
            break;
        }
        if (write(1, &byte_buf, 1) != 1) {
            perror("write (stdout)");
            break;
        }
    }
    write(1, "\n", 1);
    close(fd);
    return 0;
}
