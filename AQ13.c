#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

// Question: How to redirect standard output to a file "output.txt" using the `dup` and `open` system calls in C?

// Instructions for Windows (Note: Windows doesn't support `open` as shown below):
// 1. Open Command Prompt or PowerShell.
// 2. Compile the C program using a C compiler, e.g., MinGW for Windows:
//    Example: gcc program.c -o redirect_output.exe
// 3. Run the compiled program:
//    Example: redirect_output.exe
//    (The redirection will not work as expected on Windows; it's mainly for Unix-like systems.)

// Instructions for Ubuntu (or other Linux-based systems):
// 1. Open a terminal.
// 2. Compile the C program using a C compiler, e.g., GCC:
//    Example: gcc program.c -o redirect_output
// 3. Run the compiled program, which redirects standard output to "output.txt":
//    Example: ./redirect_output
// 4. Check the content of the "output.txt" file.

int main() {
    // Redirect standard output to "output.txt"
    int file_descriptor = open("output.txt", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
    if (file_descriptor == -1) {
        perror("open");
        return 1;
    }

    if (dup2(file_descriptor, STDOUT_FILENO) == -1) {
        perror("dup2");
        return 1;
    }

    // Print some content to the file
    printf("This is an example of standard output redirection using the `dup` and `open` system calls.\n");
    printf("The output is redirected to the 'output.txt' file.\n");

    return 0;
}
