#include <stdio.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    // Question: How can we retrieve and print the inode numbers of files using C and command-line arguments?

    // Instructions:
    // 1. Compile this C program using a C compiler (e.g., gcc).
    //    Example: gcc program.c -o program
    // 2. Run the compiled program, providing file names as command-line arguments.
    //    Example: ./program file1 file2 file3

    if (argc < 2) {
        printf("Error: No file names provided.\n");
        printf("Usage: %s file1 file2 file3 ...\n", argv[0]);
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        const char *filename = argv[i];
        struct stat file_stat;

        // Use stat to get information about the file, including the inode number
        if (stat(filename, &file_stat) == 0) {
            printf("File: %s\n", filename);
            printf("Inode Number: %lu\n", (unsigned long)file_stat.st_ino);
        } else {
            printf("Error: Could not retrieve information for %s\n", filename);
        }
    }

    return 0;
}
