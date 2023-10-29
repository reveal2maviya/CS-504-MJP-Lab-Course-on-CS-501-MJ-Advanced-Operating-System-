#include <stdio.h>
#include <stdlib.h>

int main() {
    // Question: How to create a file with a hole in C?

    // Description: This simple C program demonstrates how to create a file with a hole in it.
    // We'll write some data to the file, move the file position to create a hole, 
    // and then write more data after the hole.

    FILE *file = fopen("file_with_hole.txt", "w");
    
    if (file == NULL) {
        perror("fopen");
        return 1;
    }
    
    // Write some data to the file
    fprintf(file, "This is the first part of the file.");
    
    // Seek to create a hole
    fseek(file, 1024, SEEK_SET);
    
    // Write more data after the hole
    fprintf(file, "This is the second part of the file.");
    
    fclose(file);
    
    printf("File with a hole created successfully.\n");
    
    return 0;
}
