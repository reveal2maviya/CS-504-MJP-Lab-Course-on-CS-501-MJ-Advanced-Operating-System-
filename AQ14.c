#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

// Question: How to identify the type of a given file (Directory, character device, block device, regular file, FIFO/pipe, symbolic link, or socket) using the `stat()` system call in C?

// Instructions for Windows (Note: This program is primarily for Unix-like systems and may not work on Windows):
// 1. This program is designed for Unix-like systems and relies on POSIX-specific system calls.
// 2. To run on Windows, you may consider using a Unix-like environment or a tool like Cygwin or Windows Subsystem for Linux (WSL).
// 3. In a Unix-like environment, you can compile and run the program as follows:

// Instructions for Ubuntu (or other Linux-based systems):
// 1. Open a terminal.
// 2. Compile the C program using a C compiler, e.g., GCC:
//    Example: gcc program.c -o identify_file_type
// 3. Run the compiled program, providing the file name as an argument.
//    Example: ./identify_file_type /path/to/your/file

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <file_name>\n", argv[0]);
        return 1;
    }

    const char *file_name = argv[1];
    struct stat file_stat;

    if (stat(file_name, &file_stat) == 0) {
        printf("File Type: ");

        if (S_ISREG(file_stat.st_mode)) {
            printf("Regular File\n");
        } else if (S_ISDIR(file_stat.st_mode)) {
            printf("Directory\n");
        } else if (S_ISCHR(file_stat.st_mode)) {
            printf("Character Device\n");
        } else if (S_ISBLK(file_stat.st_mode)) {
            printf("Block Device\n");
        } else if (S_ISFIFO(file_stat.st_mode)) {
            printf("FIFO/pipe\n");
        } else if (S_ISLNK(file_stat.st_mode)) {
            printf("Symbolic Link\n");
        } else if (S_ISSOCK(file_stat.st_mode)) {
            printf("Socket\n");
        } else {
            printf("Unknown\n");
        }
    } else {
        perror("stat");
        return 1;
    }

    return 0;
}
