#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

// Global variable to track the child process ID
pid_t child_pid;

// Signal handler function for SIGUSR1 (used to resume the child process)
void sigusr1_handler(int signum) {
    printf("Child process resumed.\n");
}

// Signal handler function for SIGUSR2 (used to suspend the child process)
void sigusr2_handler(int signum) {
    printf("Child process suspended.\n");
}

// Question: How to create a C program that illustrates suspending and resuming processes using signals?

// Instructions for Windows (Note: This program is primarily for Unix-like systems and may not work on Windows):
// 1. This program is designed for Unix-like systems and relies on POSIX-specific system calls.
// 2. To run on Windows, you may consider using a Unix-like environment or a tool like Cygwin or Windows Subsystem for Linux (WSL).
// 3. In a Unix-like environment, you can compile and run the program as follows:

// Instructions for Ubuntu (or other Linux-based systems):
// 1. Open a terminal.
// 2. Compile the C program using a C compiler, e.g., GCC:
//    Example: gcc program.c -o suspend_resume_example
// 3. Run the compiled program.
// 4. The parent process can suspend and resume the child process using signals.

int main() {
    if ((child_pid = fork()) == -1) {
        perror("fork");
        return 1;
    }

    if (child_pid == 0) {
        // Child process
        signal(SIGUSR1, sigusr1_handler);
        signal(SIGUSR2, sigusr2_handler);

        while (1) {
            // Child process continues to run
        }
    } else {
        // Parent process
        int choice;

        printf("1. Suspend child process (send SIGUSR2)\n");
        printf("2. Resume child process (send SIGUSR1)\n");
        printf("3. Exit\n");

        while (1) {
            printf("Enter your choice: ");
            scanf("%d", &choice);

            switch (choice) {
                case 1:
                    // Suspend the child process
                    kill(child_pid, SIGUSR2);
                    break;
                case 2:
                    // Resume the child process
                    kill(child_pid, SIGUSR1);
                    break;
                case 3:
                    // Exit the program
                    kill(child_pid, SIGKILL);  // Terminate the child process
                    return 0;
                default:
                    printf("Invalid choice. Try again.\n");
            }
        }
    }

    return 0;
}
