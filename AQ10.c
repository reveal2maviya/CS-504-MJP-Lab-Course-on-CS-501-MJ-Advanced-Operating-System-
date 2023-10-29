#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

// Question: How to display files in the current directory whose size is greater than n Bytes?

// Instructions for Windows:
// 1. Open Command Prompt or PowerShell.
// 2. Compile the C program using a C compiler, e.g., MinGW for Windows:
//    Example: gcc program.c -o filter_files_by_size.exe
// 3. Run the compiled program, providing the size (in bytes) as an argument.
//    Example: filter_files_by_size.exe 1000

// Instructions for Ubuntu (or other Linux-based systems):
// 1. Open a terminal.
// 2. Compile the C program using a C compiler, e.g., GCC:
//    Example: gcc program.c -o filter_files_by_size
// 3. Run the compiled program, providing the size (in bytes) as an argument.
//    Example: ./filter_files_by_size 1000

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <size_in_bytes>\n", argv[0]);
        return 1;
    }

    long long int min_size = atoll(argv[1]);

    DIR *dir = opendir(".");
    if (dir == NULL) {
        perror("opendir");
        return 1;
    }

    struct dirent *entry;

    printf("Files with size greater than %lld bytes:\n", min_size);

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG) {  // Check if it's a regular file
            struct stat file_stat;
            if (stat(entry->d_name, &file_stat) == 0) {
                if (file_stat.st_size > min_size) {
                    printf("%s\n", entry->d_name);
                }
            }
        }
    }

    closedir(dir);
    return 0;
}
