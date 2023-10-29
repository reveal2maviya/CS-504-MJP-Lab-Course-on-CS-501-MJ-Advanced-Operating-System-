#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// Question: How to print the exit status of a terminated child process in C?

// Instructions for Windows (Note: This program is primarily for Unix-like systems and may not work on Windows):
// 1. This program is designed for Unix-like systems and relies on POSIX-specific system calls.
// 2. To run on Windows, you may consider using a Unix-like environment or a tool like Cygwin or Windows Subsystem for Linux (WSL).
// 3. In a Unix-like environment, you can compile and run the program as follows:

// Instructions for Ubuntu (or other Linux-based systems):
// 1. Open a terminal.
// 2. Compile the C program using a C compiler, e.g., GCC:
//    Example: gcc program.c -o exit_status_example
// 3. Run the compiled program.

int main() {
    pid_t child_pid;
    int status;

    if ((child_pid = fork()) == -1) {
        perror("fork");
        return 1;
    }

    if (child_pid == 0) {
        // Child process
        printf("Child process (PID %d) is running...\n", getpid());
        exit(42);  // Exit with status 42
    } else {
        // Parent process
        wait(&status);  // Wait for the child process to finish and get its exit status

        if (WIFEXITED(status)) {
            // Child process exited normally
            printf("Child process (PID %d) exited with status: %d\n", child_pid, WEXITSTATUS(status));
        } else {
            // Child process did not exit normally
            printf("Child process (PID %d) did not exit normally\n", child_pid);
        }
    }

    return 0;
}
