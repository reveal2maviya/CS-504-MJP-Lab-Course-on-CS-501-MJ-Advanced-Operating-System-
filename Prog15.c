/*Generate parent process to write unnamed pipe and will read from it*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main() {
    int pipefd[2]; // File descriptors for the pipe
    pid_t child_pid;

    // Create the pipe
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Create a child process
    child_pid = fork();

    if (child_pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (child_pid == 0) { // Child process
        close(pipefd[1]); // Close the write end

        char buffer[100];
        ssize_t num_bytes;

        // Read from the pipe
        num_bytes = read(pipefd[0], buffer, sizeof(buffer));
        if (num_bytes == -1) {
            perror("read");
            exit(EXIT_FAILURE);
        }

        // Null-terminate the string
        buffer[num_bytes] = '\0';

        printf("Child process received: %s\n", buffer);

        close(pipefd[0]); // Close the read end
    } else { // Parent process
        close(pipefd[0]); // Close the read end

        const char *message = "Hello from parent!";
        
        // Write to the pipe
        if (write(pipefd[1], message, strlen(message)) == -1) {
            perror("write");
            exit(EXIT_FAILURE);
        }

        close(pipefd[1]); // Close the write end
    }

    return 0;
}
