#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

// Global variable to track Ctrl-C presses
int ctrlc_count = 0;

// Signal handler function for SIGINT (Ctrl-C)
void sigint_handler(int signum) {
    if (ctrlc_count == 0) {
        // First Ctrl-C press
        printf("Press Ctrl-C again to exit.\n");
        ctrlc_count++;
    } else {
        // Second Ctrl-C press
        printf("Exiting...\n");
        exit(0);
    }
}

// Question: How to catch the Ctrl-C (SIGINT) signal for the first time and display an appropriate message, exiting on the second Ctrl-C press in C?

// Instructions for Windows (Note: This program is primarily for Unix-like systems and may not work on Windows):
// 1. This program is designed for Unix-like systems and relies on POSIX-specific system calls.
// 2. To run on Windows, you may consider using a Unix-like environment or a tool like Cygwin or Windows Subsystem for Linux (WSL).
// 3. In a Unix-like environment, you can compile and run the program as follows:

// Instructions for Ubuntu (or other Linux-based systems):
// 1. Open a terminal.
// 2. Compile the C program using a C compiler, e.g., GCC:
//    Example: gcc program.c -o ctrlc_handler_example
// 3. Run the compiled program.
// 4. To test the Ctrl-C handling, press Ctrl-C in the terminal.

int main() {
    // Register the signal handler for SIGINT (Ctrl-C)
    signal(SIGINT, sigint_handler);

    printf("Press Ctrl-C to test the signal handler.\n");

    while (1) {
        // Program loop
    }

    return 0;
}
