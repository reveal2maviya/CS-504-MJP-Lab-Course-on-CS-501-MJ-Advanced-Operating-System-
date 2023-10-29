/*Write a C program to Identify the type (Directory, character device, Block device, Regular file, FIFO or pipe, symbolic link or socket) of given file using stat() system call.*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>

void identifyFileType(const char *filename) {
    struct stat fileStat;

    if (stat(filename, &fileStat) == -1) {
        perror("Failed to get file information");
        return;
    }

    if (S_ISDIR(fileStat.st_mode)) {
        printf("%s is a directory.\n", filename);
    } else if (S_ISCHR(fileStat.st_mode)) {
        printf("%s is a character device.\n", filename);
    } else if (S_ISBLK(fileStat.st_mode)) {
        printf("%s is a block device.\n", filename);
    } else if (S_ISREG(fileStat.st_mode)) {
        printf("%s is a regular file.\n", filename);
    } else if (S_ISFIFO(fileStat.st_mode)) {
        printf("%s is a FIFO or pipe.\n", filename);
    } else if (S_ISLNK(fileStat.st_mode)) {
        printf("%s is a symbolic link.\n", filename);
    } else if (S_ISSOCK(fileStat.st_mode)) {
        printf("%s is a socket.\n", filename);
    } else {
        printf("%s is of an unknown type.\n", filename);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    identifyFileType(argv[1]);

    return 0;
}
