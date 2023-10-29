#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

int main() {
    // Question: How to list the files in the current directory and count the number of files?

    // Instructions for Windows:
    // 1. Open Command Prompt or PowerShell.
    // 2. Compile the C program using a C compiler, e.g., MinGW for Windows:
    //    Example: gcc program.c -o list_files.exe
    // 3. Run the compiled program.
    //    Example: list_files.exe

    // Instructions for Ubuntu (or other Linux-based systems):
    // 1. Open a terminal.
    // 2. Compile the C program using a C compiler, e.g., GCC:
    //    Example: gcc program.c -o list_files
    // 3. Run the compiled program.
    //    Example: ./list_files

    DIR *dir = opendir(".");
    if (dir == NULL) {
        perror("opendir");
        return 1;
    }

    int file_count = 0;

    printf("Files in the current directory:\n");

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG) {  // Check if it's a regular file
            printf("%s\n", entry->d_name);
            file_count++;
        }
    }

    closedir(dir);

    printf("\nNumber of files in the current directory: %d\n", file_count);

    return 0;
}
