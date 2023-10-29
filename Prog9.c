/*Display all the files from current directory which are created in particular month*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <month_number>\n", argv[0]);
        return 1;
    }

    int targetMonth = atoi(argv[1]);
    if (targetMonth < 1 || targetMonth > 12) {
        printf("Invalid month number. Please provide a number between 1 and 12.\n");
        return 1;
    }

    // Open the current directory
    DIR *dir = opendir(".");
    if (dir == NULL) {
        perror("Unable to open directory");
        return 1;
    }

    struct dirent *entry;
    struct tm *creationTime;
    struct stat fileStat;

    printf("Files created in month %d:\n", targetMonth);
    
    while ((entry = readdir(dir)) != NULL) {
        if (stat(entry->d_name, &fileStat) == 0) {
            creationTime = localtime(&fileStat.st_ctime);
            if (creationTime->tm_mon + 1 == targetMonth) { // tm_mon is 0-based
                printf("%s\n", entry->d_name);
            }
        }
    }

    closedir(dir);
    return 0;
}
