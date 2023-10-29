/*Write a C program to implement the following unix/linux command (use fork, pipe and exec system call). Your program should block the signal Ctrl-C and Ctrl-\ signal during the execution. i. Ls –l | wc –l*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int pipe_fd[2];
    pid_t ls_pid, wc_pid;

    if (pipe(pipe_fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    ls_pid = fork();

    if (ls_pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (ls_pid == 0) { // Child process for "ls -l"
        // Close the read end of the pipe
        close(pipe_fd[0]);

        // Redirect stdout to the write end of the pipe
        dup2(pipe_fd[1], STDOUT_FILENO);

        // Execute the "ls -l" command
        execlp("ls", "ls", "-l", NULL);

        perror("execlp (ls -l)");
        exit(EXIT_FAILURE);
    }

    // Close the write end of the pipe in the parent
    close(pipe_fd[1]);

    wc_pid = fork();

    if (wc_pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (wc_pid == 0) { // Child process for "wc -l"
        // Redirect stdin to the read end of the pipe
        dup2(pipe_fd[0], STDIN_FILENO);

        // Execute the "wc -l" command
        execlp("wc", "wc", "-l", NULL);

        perror("execlp (wc -l)");
        exit(EXIT_FAILURE);
    }

    // Close the read end of the pipe in the parent
    close(pipe_fd[0]);

    // Wait for both child processes to complete
    wait(NULL);
    wait(NULL);

    return 0;
}
