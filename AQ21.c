#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

// Question: How to create an unnamed pipe in C, where the child process writes three messages, and the parent process displays them?

// Instructions for Windows (Note: This program is primarily for Unix-like systems and may not work on Windows):
// 1. This program is designed for Unix-like systems and relies on POSIX-specific system calls.
// 2. To run on Windows, you may consider using a Unix-like environment or a tool like Cygwin or Windows Subsystem for Linux (WSL).
// 3. In a Unix-like environment, you can compile and run the program as follows:

// Instructions for Ubuntu (or other Linux-based systems):
// 1. Open a terminal.
// 2. Compile the C program using a C compiler, e.g., GCC:
//    Example: gcc program.c -o unnamed_pipe_example
// 3. Run the compiled program:
//    Example: ./unnamed_pipe_example

int main() {
    int pipe_fd[2];
    pid_t child_pid;
    char messages[3][128] = {"Hello World", "Hello SPPU", "Linux is Funny"};

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
        close(pipe_fd[0]);  // Close read end

        // Write three messages to the pipe
        for (int i = 0; i < 3; i++) {
            write(pipe_fd[1], messages[i], strlen(messages[i]) + 1);
        }

        close(pipe_fd[1]);
    } else {
        // Parent process
        close(pipe_fd[1]);  // Close write end

        char buffer[128];
        int bytes_read;

        // Read and display the messages from the pipe
        while ((bytes_read = read(pipe_fd[0], buffer, sizeof(buffer))) > 0) {
            printf("Received: %s\n", buffer);
        }

        close(pipe_fd[0]);
    }

    return 0;
}
