#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

// Question: How to display file names in ascending order according to their sizes?

// Instructions for Windows:
// 1. Open Command Prompt or PowerShell.
// 2. Compile the C program using a C compiler, e.g., MinGW for Windows:
//    Example: gcc program.c -o sort_files.exe
// 3. Run the compiled program, providing file names as command-line arguments.
//    Example: sort_files.exe file1.txt file2.txt file3.txt

// Instructions for Ubuntu (or other Linux-based systems):
// 1. Open a terminal.
// 2. Compile the C program using a C compiler, e.g., GCC:
//    Example: gcc program.c -o sort_files
// 3. Run the compiled program, providing file names as command-line arguments.
//    Example: ./sort_files file1.txt file2.txt file3.txt

int compare(const void *a, const void *b) {
    struct stat file1_stat, file2_stat;
    stat(*(char **)a, &file1_stat);
    stat(*(char **)b, &file2_stat);
    return (int)(file1_stat.st_size - file2_stat.st_size);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s file1 file2 file3 ...\n", argv[0]);
        return 1;
    }

    // Sort file names according to their sizes
    qsort(argv + 1, argc - 1, sizeof(char *), compare);

    // Display sorted file names
    printf("File names in ascending order of sizes:\n");
    for (int i = 1; i < argc; i++) {
        printf("%s\n", argv[i]);
    }
    
    return 0;
}
