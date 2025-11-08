#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

int main() {
    const char *filename = "numbers.txt";
    int fd;

    printf("Task 6: Writing numbers 1-10 to '%s'\n", filename);
    fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror("open (write)");
        return 1;
    }

    char line[16];
    for (int i = 1; i <= 10; i++) {
        int len = sprintf(line, "%d\n", i);
        if (write(fd, line, len) != len) {
            perror("write (numbers)");
            close(fd);
            return 1;
        }
    }
    close(fd);

    printf("Task 6: Reopening O_RDWR to overwrite line 4...\n");
    fd = open(filename, O_RDWR);
    if (fd < 0) {
        perror("open (rdwr)");
        return 1;
    }

    off_t offset_line_4 = 0;
    int newline_count = 0;
    char buf;
    while (read(fd, &buf, 1) > 0) {
        if (buf == '\n') {
            newline_count++;
        }
        if (newline_count == 3) {
            break;
        }
    }

    offset_line_4 = lseek(fd, 0, SEEK_CUR);
    if (newline_count != 3) {
        fprintf(stderr, "Task 6: Error: File does not have 4 lines.\n");
        close(fd);
        return 1;
    }

    off_t offset_line_5 = offset_line_4;
    while (read(fd, &buf, 1) > 0) {
        offset_line_5++;
        if (buf == '\n') {
            break;
        }
    }

    off_t total_size = lseek(fd, 0, SEEK_END);
    off_t remainder_size = total_size - offset_line_5;

    char *remainder_buf = malloc(remainder_size);
    if (remainder_size > 0 && !remainder_buf) {
        perror("malloc");
        close(fd);
        return 1;
    }

    if (remainder_size > 0) {
        lseek(fd, offset_line_5, SEEK_SET);
        if (read(fd, remainder_buf, remainder_size) != remainder_size) {
            perror("read (remainder)");
            free(remainder_buf);
            close(fd);
            return 1;
        }
    }

    lseek(fd, offset_line_4, SEEK_SET);

    const char *new_line = "100\n";
    printf("Task 6: Overwriting '4\\n' with '100\\n' at offset %ld\n", (long)offset_line_4);
    if (write(fd, new_line, strlen(new_line)) != strlen(new_line)) {
        perror("write (overwrite)");
        free(remainder_buf);
        close(fd);
        return 1;
    }

    if (remainder_size > 0) {
        if (write(fd, remainder_buf, remainder_size) != remainder_size) {
            perror("write (remainder)");
            free(remainder_buf);
            close(fd);
            return 1;
        }
    }

    off_t new_pos = lseek(fd, 0, SEEK_CUR);
    if (ftruncate(fd, new_pos) < 0) {
        perror("ftruncate (cleanup)");
    }

    free(remainder_buf);

    printf("--- Task 6 Final Content ---\n");
    lseek(fd, 0, SEEK_SET);
    char read_buf[256];
    ssize_t bytes_read_verify;
    while ((bytes_read_verify = read(fd, read_buf, sizeof(read_buf))) > 0) {
        write(1, read_buf, bytes_read_verify);
    }
    printf("----------------------------\n");
    close(fd);
    return 0;
}
