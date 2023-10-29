#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

// Question: How to handle two-way communication between parent and child processes using a pipe in C?

// Instructions for Windows (Note: This program is primarily for Unix-like systems and may not work on Windows):
// 1. This program is designed for Unix-like systems and relies on POSIX-specific system calls.
// 2. To run on Windows, you may consider using a Unix-like environment or a tool like Cygwin or Windows Subsystem for Linux (WSL).
// 3. In a Unix-like environment, you can compile and run the program as follows:

// Instructions for Ubuntu (or other Linux-based systems):
// 1. Open a terminal.
// 2. Compile the C program using a C compiler, e.g., GCC:
//    Example: gcc program.c -o two_way_pipe
// 3. Run the compiled program:
//    Example: ./two_way_pipe

int main() {
    int pipe_fd[2];
    pid_t child_pid;

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

        // Sending a response to the parent
        char response[] = "Hello, parent!";
        ssize_t bytes_written = write(pipe_fd[0], response, sizeof(response));
        if (bytes_written == -1) {
            perror("write");
            return 1;
        }

        close(pipe_fd[0]);
    } else {
        // Parent process
        close(pipe_fd[0]);  // Close read end

        char message[] = "Hello, child!";
        ssize_t bytes_written = write(pipe_fd[1], message, sizeof(message));
        if (bytes_written == -1) {
            perror("write");
            return 1;
        }

        // Receiving the child's response
        char response_buffer[256];
        ssize_t response_read = read(pipe_fd[1], response_buffer, sizeof(response_buffer));
        if (response_read == -1) {
            perror("read");
            return 1;
        }

        printf("Parent received: %s\n", response_buffer);

        close(pipe_fd[1]);
        wait(NULL);
    }

    return 0;
}
