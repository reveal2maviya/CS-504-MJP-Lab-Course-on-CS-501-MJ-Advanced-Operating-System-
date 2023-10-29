/*Write a C program that print the exit status of a terminated child process*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t child_pid;
    int status;

    child_pid = fork();

    if (child_pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (child_pid == 0) { // Child process
        // Simulate some work in the child process
        for (int i = 0; i < 1000000; i++) {
            // Do some computation
        }
        exit(42); // Exit with a specific status code
    } else { // Parent process
        // Wait for the child process to terminate and get its exit status
        if (wait(&status) != -1) {
            if (WIFEXITED(status)) {
                printf("Child process exited with status: %d\n", WEXITSTATUS(status));
            } else if (WIFSIGNALED(status)) {
                printf("Child process terminated by signal: %d\n", WTERMSIG(status));
            }
        } else {
            perror("wait");
        }
    }

    return 0;
}
