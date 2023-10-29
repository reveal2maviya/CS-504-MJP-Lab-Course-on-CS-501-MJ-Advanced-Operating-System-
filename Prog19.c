/*Implement the following unix/linux command (use fork, pipe and exec system call)
ls –l | wc –l*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int pipe_fd[2];
    pid_t ls_pid, wc_pid;

    // Create a pipe
    if (pipe(pipe_fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Create the first child process for 'ls -l'
    ls_pid = fork();

    if (ls_pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (ls_pid == 0) { // Child process
        // Redirect the standard output to the write end of the pipe
        close(pipe_fd[0]); // Close the read end
        dup2(pipe_fd[1], STDOUT_FILENO);

        // Execute 'ls -l'
        execlp("ls", "ls", "-l", NULL);

        perror("execlp (ls)");
        exit(EXIT_FAILURE);
    } else { // Parent process
        // Create the second child process for 'wc -l'
        wc_pid = fork();

        if (wc_pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (wc_pid == 0) { // Child process
            // Redirect the standard input to the read end of the pipe
            close(pipe_fd[1]); // Close the write end
            dup2(pipe_fd[0], STDIN_FILENO);

            // Execute 'wc -l'
            execlp("wc", "wc", "-l", NULL);

            perror("execlp (wc)");
            exit(EXIT_FAILURE);
        } else { // Parent process
            // Close both ends of the pipe
            close(pipe_fd[0]);
            close(pipe_fd[1]);

            // Wait for both child processes to complete
            wait(NULL);
            wait(NULL);
        }
    }

    return 0;
}
