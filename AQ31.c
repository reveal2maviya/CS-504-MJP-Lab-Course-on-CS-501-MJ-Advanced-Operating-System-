#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

// Global variable to track the child process ID
pid_t child_pid;

// Signal handler function for the death of child signal (SIGCHLD)
void sigchld_handler(int signum) {
    int status;
    pid_t terminated_pid;

    terminated_pid = wait(&status);

    if (WIFEXITED(status)) {
        printf("Child process with PID %d terminated normally with exit status %d.\n", terminated_pid, WEXITSTATUS(status));
    } else if (WIFSIGNALED(status)) {
        printf("Child process with PID %d terminated by signal %d.\n", terminated_pid, WTERMSIG(status));
    }
}

// Signal handler function for the alarm signal (SIGALRM)
void sigalarm_handler(int signum) {
    printf("Child process exceeded the time limit and is killed.\n");
    kill(child_pid, SIGKILL);  // Terminate the child process
}

// Question: How to create a C program that creates a child process to run a Linux/Unix command or any user-defined program, and if the child process doesn't complete its execution within 5 seconds, the parent process kills it?

// Instructions for Windows (Note: This program is primarily for Unix-like systems and may not work on Windows):
// 1. This program is designed for Unix-like systems and relies on POSIX-specific system calls.
// 2. To run on Windows, you may consider using a Unix-like environment or a tool like Cygwin or Windows Subsystem for Linux (WSL).
// 3. In a Unix-like environment, you can compile and run the program as follows:

// Instructions for Ubuntu (or other Linux-based systems):
// 1. Open a terminal.
// 2. Compile the C program using a C compiler, e.g., GCC:
//    Example: gcc program.c -o child_execution_example
// 3. Run the compiled program.
// 4. The program will create a child process, set signal handlers, and terminate the child process if it exceeds the time limit (5 seconds).

int main() {
    // Register the signal handler for the death of child (SIGCHLD) signal
    signal(SIGCHLD, sigchld_handler);

    if ((child_pid = fork()) == -1) {
        perror("fork");
        return 1;
    }

    if (child_pid == 0) {
        // Child process
        // Replace the command and its arguments with the desired program to run
        execlp("ls", "ls", "-l", NULL);
        perror("execlp");
        exit(1);
    } else {
        // Parent process
        // Set the alarm to terminate the child process after 5 seconds
        alarm(5);
        // Wait for the child process to complete
        wait(NULL);
    }

    return 0;
}
