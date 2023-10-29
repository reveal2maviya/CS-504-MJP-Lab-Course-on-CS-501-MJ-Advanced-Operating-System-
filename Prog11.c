/*Write a C Program that demonstrates redirection of standard output to a file.*/
#include <stdio.h>

int main() {
    // Store the original stdout
    FILE *original_stdout = stdout;

    // Open a file for writing
    FILE *file = fopen("output.txt", "w");
    if (file == NULL) {
        perror("Unable to open the file");
        return 1;
    }

    // Redirect stdout to the file
    if (dup2(fileno(file), fileno(stdout)) == -1) {
        perror("Unable to redirect stdout");
        return 1;
    }

    // Now, stdout is redirected to the "output.txt" file
    printf("This is redirected to a file.\n");

    // Restore the original stdout
    fflush(stdout);  // Flush any remaining output
    dup2(fileno(original_stdout), fileno(stdout));  // Redirect back to the original stdout

    printf("This is back to the original stdout.\n");

    // Close the file
    fclose(file);

    return 0;
}
