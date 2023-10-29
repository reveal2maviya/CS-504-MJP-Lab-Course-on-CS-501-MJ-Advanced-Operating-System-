#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

// Global variable to track the child process ID
pid_t child_pid;

// Signal handler function for SIGALRM
void sigalrm_handler(int signum) {
    printf("Alarm is fired.\n");
}

// Question: How to create a C program where a child process sends a SIGALRM signal to the parent process, and the parent process catches the signal and displays "Alarm is fired"?

// Instructions for Windows (Note: This program is primarily for Unix-like systems and may not work on Windows):
// 1. This program is designed for Unix-like systems and relies on POSIX-specific system calls.
// 2. To run on Windows, you may consider using a Unix-like environment or a tool like Cygwin or Windows Subsystem for Linux (WSL).
// 3. In a Unix-like environment, you can compile and run the program as follows:

// Instructions for Ubuntu (or other Linux-based systems):
// 1. Open a terminal.
// 2. Compile the C program using a C compiler, e.g., GCC:
//    Example: gcc program.c -o sigalrm_example
// 3. Run the compiled program.
// 4. The parent process will catch the SIGALRM signal sent by the child process and display "Alarm is fired."

int main() {
    signal(SIGALRM, sigalrm_handler);

    if ((child_pid = fork()) == -1) {
        perror("fork");
        return 1;
    }

    if (child_pid == 0) {
        // Child process
        sleep(3);  // Sleep for 3 seconds

        // Send SIGALRM to the parent process
        kill(getppid(), SIGALRM);

        exit(0);
    } else {
        // Parent process
        while (1) {
            // Parent process continues to run
        }
    }

    return 0;
}
