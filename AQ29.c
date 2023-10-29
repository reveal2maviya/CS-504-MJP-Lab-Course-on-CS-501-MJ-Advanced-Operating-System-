#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

// Global variable to track the child process ID
pid_t child_pid;

// Signal handler function for SIGHUP
void sighup_handler(int signum) {
    printf("Child received SIGHUP signal from parent.\n");
}

// Signal handler function for SIGINT
void sigint_handler(int signum) {
    printf("Child received SIGINT signal from parent.\n");
}

// Signal handler function for SIGQUIT
void sigquit_handler(int signum) {
    printf("Child received SIGQUIT signal from parent and is terminating: My DADDY has Killed me!!!\n");
    exit(0);
}

// Question: How to create a C program where a child process catches SIGHUP, SIGINT, and SIGQUIT signals, and the parent process sends signals to the child according to specified intervals?

// Instructions for Windows (Note: This program is primarily for Unix-like systems and may not work on Windows):
// 1. This program is designed for Unix-like systems and relies on POSIX-specific system calls.
// 2. To run on Windows, you may consider using a Unix-like environment or a tool like Cygwin or Windows Subsystem for Linux (WSL).
// 3. In a Unix-like environment, you can compile and run the program as follows:

// Instructions for Ubuntu (or other Linux-based systems):
// 1. Open a terminal.
// 2. Compile the C program using a C compiler, e.g., GCC:
//    Example: gcc program.c -o daddy_killed_me_example
// 3. Run the compiled program.
// 4. The parent process will send signals to the child process as described.

int main() {
    if ((child_pid = fork()) == -1) {
        perror("fork");
        return 1;
    }

    if (child_pid == 0) {
        // Child process
        signal(SIGHUP, sighup_handler);
        signal(SIGINT, sigint_handler);
        signal(SIGQUIT, sigquit_handler);

        while (1) {
            // Child process continues to run
        }
    } else {
        // Parent process
        int seconds = 0;
        int max_seconds = 30;

        while (seconds < max_seconds) {
            sleep(3);  // Sleep for 3 seconds

            // Send SIGHUP to the child process every 3 seconds
            if (seconds % 6 == 0) {
                kill(child_pid, SIGHUP);
            } else {
                kill(child_pid, SIGINT);
            }

            seconds += 3;
        }

        // Send SIGQUIT to the child process after 30 seconds
        kill(child_pid, SIGQUIT);

        // Wait for the child process to terminate
        wait(NULL);
    }

    return 0;
}
