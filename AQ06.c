#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

int main(int argc, char *argv[]) {
    // Question: How to list files in the current directory that begin with a specific string?
    // Description: This C program takes a string as an argument and searches for files in the current directory that have names starting with the provided string. It uses the opendir and readdir functions to traverse the directory and compare file names.
    
    // Instructions for Windows:
    // 1. Open a command prompt (CMD) or PowerShell.
    // 2. Compile the program using a C compiler (e.g., MinGW for Windows):
    //    Example: gcc program.c -o a.exe
    // 3. Run the compiled program, providing the string as an argument:
    //    Example: a.exe foo

    // Instructions for Ubuntu (or other Linux-based systems):
    // 1. Open a terminal.
    // 2. Compile the program using a C compiler (e.g., GCC):
    //    Example: gcc program.c -o a.out
    // 3. Run the compiled program, providing the string as an argument:
    //    Example: ./a.out foo

    // Check if the user provided a string as an argument
    if (argc != 2) {
        printf("Usage: %s <string>\n", argv[0]);
        return 1;
    }

    // Open the current directory
    DIR *dir = opendir(".");
    if (dir == NULL) {
        perror("opendir");
        return 1;
    }

    // Get the length of the provided string
    const char *search_string = argv[1];
    size_t search_length = strlen(search_string);

    // Read and compare file names
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG) {  // Check if it's a regular file
            if (strncmp(entry->d_name, search_string, search_length) == 0) {
                printf("%s\n", entry->d_name);
            }
        }
    }

    closedir(dir);
    return 0;
}