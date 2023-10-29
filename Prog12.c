/*Write a C program that will only list all subdirectories in alphabetical order from current directory.*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

int main() {
    // Open the current directory
    DIR *dir = opendir(".");
    if (dir == NULL) {
        perror("Unable to open directory");
        return 1;
    }

    struct dirent *entry;
    printf("Subdirectories in alphabetical order:\n");

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_DIR) {
            if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
                printf("%s\n", entry->d_name);
            }
        }
    }

    closedir(dir);
    return 0;
}
