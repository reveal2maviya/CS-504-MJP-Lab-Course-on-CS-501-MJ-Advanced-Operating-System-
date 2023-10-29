/*Display all the files from current directory whose size is greater that n Bytes Where n is accept from user.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <size_in_bytes>\n", argv[0]);
        return 1;
    }

    long long targetSize = atoll(argv[1]);
    if (targetSize < 0) {
        printf("Invalid size. Please provide a non-negative size in bytes.\n");
        return 1;
    }

    // Open the current directory
    DIR *dir = opendir(".");
    if (dir == NULL) {
        perror("Unable to open directory");
        return 1;
    }

    struct dirent *entry;
    struct stat fileStat;

    printf("Files with a size greater than %lld bytes:\n", targetSize);

    while ((entry = readdir(dir)) != NULL) {
        if (stat(entry->d_name, &fileStat) == 0) {
            if (fileStat.st_size > targetSize) {
                printf("%s (%lld bytes)\n", entry->d_name, fileStat.st_size);
            }
        }
    }

    closedir(dir);
    return 0;
}
