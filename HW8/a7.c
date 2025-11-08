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
    char path1[256], path2[256];

    write(1, "Task 7: Enter first file: ", 26);
    read_line(0, path1, sizeof(path1));
    write(1, "Task 7: Enter second file: ", 27);
    read_line(0, path2, sizeof(path2));

    int fd1 = open(path1, O_RDONLY);
    if (fd1 < 0) {
        perror("open(file1)");
        return 1;
    }
    int fd2 = open(path2, O_RDONLY);
    if (fd2 < 0) {
        perror("open(file2)");
        close(fd1);
        return 1;
    }

    char buf1[4096], buf2[4096];
    ssize_t bytes1, bytes2;
    long long total_bytes = 0;
    int files_differ = 0;

    while (1) {
        bytes1 = read(fd1, buf1, sizeof(buf1));
        bytes2 = read(fd2, buf2, sizeof(buf2));

        if (bytes1 < 0) {
            perror("read(file1)");
            files_differ = 1;
            break;
        }
        if (bytes2 < 0) {
            perror("read(file2)");
            files_differ = 1;
            break;
        }

        ssize_t compare_len = (bytes1 < bytes2) ? bytes1 : bytes2;

        if (compare_len > 0 && memcmp(buf1, buf2, compare_len) != 0) {
            for (int i = 0; i < compare_len; i++) {
                if (buf1[i] != buf2[i]) {
                    printf("Task 7: Files differ at byte %lld\n", total_bytes + i);
                    files_differ = 1;
                    break;
                }
            }
            if (files_differ) break;
        }

        if (bytes1 != bytes2) {
            printf("Task 7: Files differ at byte %lld\n", total_bytes + compare_len);
            files_differ = 1;
            break;
        }

        if (bytes1 == 0) {
            break;
        }

        total_bytes += bytes1;
    }

    close(fd1);
    close(fd2);

    if (!files_differ) {
        printf("Task 7: Files are identical\n");
        return 0;
    } else {
        return 1;
    }
}
