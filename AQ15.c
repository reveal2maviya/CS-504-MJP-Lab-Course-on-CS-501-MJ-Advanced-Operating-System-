#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

// Question: How to create a parent process to write to an unnamed pipe and a child process to read from it in C?

// Instructions for Windows (Note: This program is primarily for Unix-like systems and may not work on Windows):
// 1. This program is designed for Unix-like systems and relies on POSIX-specific system calls.
// 2. To run on Windows, you may consider using a Unix-like environment or a tool like Cygwin or Windows Subsystem for Linux (WSL).
// 3. In a Unix-like environment, you can compile and run the program as follows:

// Instructions for Ubuntu (or other Linux-based systems):
// 1. Open a terminal.
// 2. Compile the C program using a C compiler, e.g., GCC:
//    Example: gcc program.c -o pipe_example
// 3. Run the compiled program:
//    Example: ./pipe_example

int main() {
    int pipe_fd[2];
    pid_t child_pid;
    char message[] = "Hello, child!";

    if (pipe(pipe_fd) == -1) {
        perror("pipe");
        return 1;
    }

    if ((child_pid = fork()) == -1) {
        perror("fork");
        return 1;
    }

    if (child_pid == 0) {
        // Child process
        close(pipe_fd[1]);  // Close write end

        char buffer[256];
        ssize_t bytes_read = read(pipe_fd[0], buffer, sizeof(buffer));
        if (bytes_read == -1) {
            perror("read");
            return 1;
        }

        printf("Child received: %s\n", buffer);
        close(pipe_fd[0]);
    } else {
        // Parent process
        close(pipe_fd[0]);  // Close read end

        ssize_t bytes_written = write(pipe_fd[1], message, strlen(message));
        if (bytes_written == -1) {
            perror("write");
            return 1;
        }

        close(pipe_fd[1]);
        wait(NULL);
    }

    return 0;
}
