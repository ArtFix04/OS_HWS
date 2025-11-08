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
    char src_path[256];
    char dst_path[256];

    write(1, "Task 1: Enter source file: ", 27);
    read_line(0, src_path, sizeof(src_path));
    write(1, "Task 1: Enter destination file: ", 32);
    read_line(0, dst_path, sizeof(dst_path));

    int fd_src = open(src_path, O_RDONLY);
    if (fd_src < 0) {
        perror("open(source)");
        return 1;
    }

    int fd_dst = open(dst_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd_dst < 0) {
        perror("open(destination)");
        close(fd_src);
        return 1;
    }

    char buffer[4096];
    ssize_t bytes_read, bytes_written;
    long long total_bytes = 0;

    while ((bytes_read = read(fd_src, buffer, sizeof(buffer))) > 0) {
        bytes_written = write(fd_dst, buffer, bytes_read);
        if (bytes_written != bytes_read) {
            perror("write");
            close(fd_src);
            close(fd_dst);
            return 1;
        }
        total_bytes += bytes_written;
    }

    if (bytes_read < 0) {
        perror("read");
    }

    printf("Task 1: Copied %lld bytes from '%s' to '%s'.\n", total_bytes, src_path, dst_path);
    close(fd_src);
    close(fd_dst);
    return 0;
}
