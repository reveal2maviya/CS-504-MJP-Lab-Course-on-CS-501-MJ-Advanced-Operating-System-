#include <stdio.h>
#include <stdlib.h>

// Question: How to demonstrate the use of the atexit() function to register cleanup functions in C?

// Instructions for Windows (Note: This program is primarily for Unix-like systems and may not work on Windows):
// 1. This program is designed for Unix-like systems and relies on POSIX-specific features.
// 2. To run on Windows, you may consider using a Unix-like environment or a tool like Cygwin or Windows Subsystem for Linux (WSL).
// 3. In a Unix-like environment, you can compile and run the program as follows:

// Instructions for Ubuntu (or other Linux-based systems):
// 1. Open a terminal.
// 2. Compile the C program using a C compiler, e.g., GCC:
//    Example: gcc program.c -o atexit_example
// 3. Run the compiled program:
//    Example: ./atexit_example

void cleanup_function1() {
    printf("Cleanup Function 1 executed.\n");
}

void cleanup_function2() {
    printf("Cleanup Function 2 executed.\n");
}

int main() {
    // Register cleanup functions using atexit()
    if (atexit(cleanup_function1) != 0) {
        perror("atexit");
        return 1;
    }
    if (atexit(cleanup_function2) != 0) {
        perror("atexit");
        return 1;
    }

    printf("Main program is running.\n");

    // Demonstrate program exit
    exit(0);
}
