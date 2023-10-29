#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

// Question: How to list all subdirectories in alphabetical order from the current directory?

// Instructions for Windows:
// 1. Open Command Prompt or PowerShell.
// 2. Compile the C program using a C compiler, e.g., MinGW for Windows:
//    Example: gcc program.c -o list_subdirectories.exe
// 3. Run the compiled program.
//    Example: list_subdirectories.exe

// Instructions for Ubuntu (or other Linux-based systems):
// 1. Open a terminal.
// 2. Compile the C program using a C compiler, e.g., GCC:
//    Example: gcc program.c -o list_subdirectories
// 3. Run the compiled program.
//    Example: ./list_subdirectories

int main() {
    DIR *dir = opendir(".");
    if (dir == NULL) {
        perror("opendir");
        return 1;
    }

    printf("Subdirectories in alphabetical order:\n");

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_DIR) {  // Check if it's a subdirectory
            if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
                printf("%s\n", entry->d_name);
            }
        }
    }

    closedir(dir);
    return 0;
}
