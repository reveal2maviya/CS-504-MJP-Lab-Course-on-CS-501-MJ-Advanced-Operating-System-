/*Write a program that illustrates how to execute two commands concurrently with a pipe.*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int pipe_fd[2];
    pid_t child1_pid, child2_pid;

    if (pipe(pipe_fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    child1_pid = fork();

    if (child1_pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (child1_pid == 0) { // Child process 1
        close(pipe_fd[0]); // Close the read end of the pipe

        // Redirect the standard output to the write end of the pipe
        dup2(pipe_fd[1], STDOUT_FILENO);

        // Execute the first command (e.g., "ls")
        execlp("ls", "ls", NULL);

        perror("execlp (ls)");
        exit(EXIT_FAILURE);
    } else {
        close(pipe_fd[1]); // Close the write end of the pipe

        child2_pid = fork();

        if (child2_pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (child2_pid == 0) { // Child process 2
            // Redirect the standard input to the read end of the pipe
            dup2(pipe_fd[0], STDIN_FILENO);

            // Execute the second command (e.g., "wc -l")
            execlp("wc", "wc", "-l", NULL);

            perror("execlp (wc)");
            exit(EXIT_FAILURE);
        } else { // Parent process
            close(pipe_fd[0]); // Close the read end of the pipe

            // Wait for both child processes to complete
            wait(NULL);
            wait(NULL);
        }
    }

    return 0;
}
