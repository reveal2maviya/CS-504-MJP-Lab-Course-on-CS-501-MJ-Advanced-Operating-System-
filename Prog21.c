/*Write a C program to create an unnamed pipe. The child process will write following three messages to pipe and parent process display it.
Message1 = “Hello World”
Message2 = “Hello SPPU”
Message3 = “Linux is Funny”*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {
    int pipe_fd[2];
    pid_t child_pid;

    if (pipe(pipe_fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    child_pid = fork();

    if (child_pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (child_pid == 0) { // Child process
        close(pipe_fd[0]); // Close the read end of the pipe

        const char *message1 = "Hello World";
        const char *message2 = "Hello SPPU";
        const char *message3 = "Linux is Funny";

        // Write messages to the pipe
        write(pipe_fd[1], message1, strlen(message1));
        write(pipe_fd[1], message2, strlen(message2));
        write(pipe_fd[1], message3, strlen(message3));

        close(pipe_fd[1]); // Close the write end of the pipe
    } else { // Parent process
        close(pipe_fd[1]); // Close the write end of the pipe

        char buffer[1024];
        ssize_t num_bytes;

        while ((num_bytes = read(pipe_fd[0], buffer, sizeof(buffer))) > 0) {
            buffer[num_bytes] = '\0';
            printf("Parent received: %s\n", buffer);
        }

        close(pipe_fd[0]); // Close the read end of the pipe
    }

    return 0;
}
