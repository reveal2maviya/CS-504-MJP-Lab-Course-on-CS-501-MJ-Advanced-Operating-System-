#include <stdio.h>

// Question: How to demonstrate redirection of standard output to a file in C?

// Instructions for Windows:
// 1. Open Command Prompt or PowerShell.
// 2. Compile the C program using a C compiler, e.g., MinGW for Windows:
//    Example: gcc program.c -o redirect_output.exe
// 3. Run the compiled program with standard output redirection to a file:
//    Example: redirect_output.exe > output.txt
// 4. Check the content of the "output.txt" file.

// Instructions for Ubuntu (or other Linux-based systems):
// 1. Open a terminal.
// 2. Compile the C program using a C compiler, e.g., GCC:
//    Example: gcc program.c -o redirect_output
// 3. Run the compiled program with standard output redirection to a file:
//    Example: ./redirect_output > output.txt
// 4. Check the content of the "output.txt" file.

int main() {
    // Redirect standard output to a file
    freopen("output.txt", "w", stdout);

    // Print some content to the file
    printf("This is an example of standard output redirection.\n");
    printf("The output is redirected to the 'output.txt' file.\n");

    return 0;
}
