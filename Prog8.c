/* Write a C program which receives file names as command line arguments and display
 those filenames in ascending order according to their sizes. I)
  (e.g $ a.out a.txt b.txt c.txt, …)*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

// Function to compare file sizes for sorting
int compareSizes(const void *a, const void *b) {
    return ((struct stat *)a)->st_size - ((struct stat *)b)->st_size;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <file1> <file2> <file3> ...\n", argv[0]);
        return 1;
    }

    // Create an array of 'stat' structures to store file information
    struct stat *fileStats = (struct stat *)malloc((argc - 1) * sizeof(struct stat));
    if (fileStats == NULL) {
        perror("Failed to allocate memory");
        return 1;
    }

    // Get file sizes and store them in the 'fileStats' array
    for (int i = 1; i < argc; i++) {
        if (stat(argv[i], &fileStats[i - 1]) != 0) {
            perror("Failed to get file information");
            free(fileStats);
            return 1;
        }
    }

    // Sort the 'fileStats' array based on file sizes
    qsort(fileStats, argc - 1, sizeof(struct stat), compareSizes);

    // Display the file names in ascending order of size
    printf("File names in ascending order of size:\n");
    for (int i = 0; i < argc - 1; i++) {
        printf("%s - %ld bytes\n", argv[i + 1], fileStats[i].st_size);
    }

    // Free the dynamically allocated memory
    free(fileStats);

    return 0;
}
