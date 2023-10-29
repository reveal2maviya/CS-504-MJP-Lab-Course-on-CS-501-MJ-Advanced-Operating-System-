#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>

// Question: How to display files in the current directory created in a particular month?

// Instructions for Windows:
// 1. Open Command Prompt or PowerShell.
// 2. Compile the C program using a C compiler, e.g., MinGW for Windows:
//    Example: gcc program.c -o filter_files.exe
// 3. Run the compiled program, providing the desired month as an argument (e.g., "01" for January).
//    Example: filter_files.exe 01

// Instructions for Ubuntu (or other Linux-based systems):
// 1. Open a terminal.
// 2. Compile the C program using a C compiler, e.g., GCC:
//    Example: gcc program.c -o filter_files
// 3. Run the compiled program, providing the desired month as an argument (e.g., "01" for January).
//    Example: ./filter_files 01

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <month>\n", argv[0]);
        return 1;
    }

    char *target_month = argv[1];

    DIR *dir = opendir(".");
    if (dir == NULL) {
        perror("opendir");
        return 1;
    }

    struct dirent *entry;
    struct tm file_time;
    char file_month[3];

    printf("Files created in month %s:\n", target_month);

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG) {  // Check if it's a regular file
            struct stat file_stat;
            if (stat(entry->d_name, &file_stat) == 0) {
                localtime_r(&file_stat.st_ctime, &file_time);
                strftime(file_month, sizeof(file_month), "%m", &file_time);
                if (strcmp(file_month, target_month) == 0) {
                    printf("%s\n", entry->d_name);
                }
            }
        }
    }

    closedir(dir);
    return 0;
}
