#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// Question: How to execute two commands concurrently with a pipe in C?

// Instructions for Windows (Note: This program is primarily for Unix-like systems and may not work on Windows):
// 1. This program is designed for Unix-like systems and relies on POSIX-specific system calls.
// 2. To run on Windows, you may consider using a Unix-like environment or a tool like Cygwin or Windows Subsystem for Linux (WSL).
// 3. In a Unix-like environment, you can compile and run the program as follows:

// Instructions for Ubuntu (or other Linux-based systems):
// 1. Open a terminal.
// 2. Compile the C program using a C compiler, e.g., GCC:
//    Example: gcc program.c -o concurrent_commands
// 3. Run the compiled program.

int main() {
    int pipe_fd[2];
    pid_t child1_pid, child2_pid;

    if (pipe(pipe_fd) == -1) {
        perror("pipe");
        return 1;
    }

    if ((child1_pid = fork()) == -1) {
        perror("fork");
        return 1;
    }

    if (child1_pid == 0) {
        // Child process 1
        close(pipe_fd[0]);  // Close read end
        dup2(pipe_fd[1], STDOUT_FILENO);  // Redirect standard output to the write end of the pipe
        close(pipe_fd[1]);  // Close the original write end

        // Execute the first command (e.g., "ls")
        execlp("ls", "ls", NULL);
        perror("execlp ls");
        exit(1);
    } else {
        if ((child2_pid = fork()) == -1) {
            perror("fork");
            return 1;
        }

        if (child2_pid == 0) {
            // Child process 2
            close(pipe_fd[1]);  // Close write end
            dup2(pipe_fd[0], STDIN_FILENO);  // Redirect standard input to the read end of the pipe
            close(pipe_fd[0]);  // Close the original read end

            // Execute the second command (e.g., "wc -l")
            execlp("wc", "wc", "-l", NULL);
            perror("execlp wc");
            exit(1);
        } else {
            // Parent process
            close(pipe_fd[0]);  // Close read end
            close(pipe_fd[1]);  // Close write end

            wait(NULL);  // Wait for both child processes to finish
            wait(NULL);
        }
    }

    return 0;
}
