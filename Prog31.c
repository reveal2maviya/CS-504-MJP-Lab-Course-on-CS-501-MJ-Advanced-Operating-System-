/*Write a C program which creates a child process to run linux/ unix command or any user defined program. The parent process set the signal handler for death of child signal and Alarm signal. If a child process does not complete its execution in 5 second then parent process kills child process*/
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

pid_t child_pid;

// Signal handler for child termination and alarm
void signalHandler(int signum) {
    if (signum == SIGCHLD) {
        int status;
        pid_t terminated_pid = wait(&status);
        if (terminated_pid == child_pid) {
            if (WIFEXITED(status)) {
                printf("Child process (PID %d) exited with status: %d\n", terminated_pid, WEXITSTATUS(status));
            } else if (WIFSIGNALED(status)) {
                printf("Child process (PID %d) terminated by signal: %d\n", terminated_pid, WTERMSIG(status));
            }
        }
    } else if (signum == SIGALRM) {
        printf("Child process execution timed out. Killing child process...\n");
        kill(child_pid, SIGKILL);
    }
}

int main() {
    // Set up signal handlers
    signal(SIGCHLD, signalHandler); // Handle child termination
    signal(SIGALRM, signalHandler); // Handle alarm signal

    child_pid = fork();

    if (child_pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (child_pid == 0) { // Child process
        // Replace with the command or program you want to run
        execlp("sleep", "sleep", "10", NULL);
        perror("execlp");
        exit(EXIT_FAILURE);
    } else { // Parent process
        // Set an alarm for 5 seconds
        alarm(5);

        // Wait for the child process to complete
        int status;
        wait(&status);

        // Cancel the alarm
        alarm(0);
    }

    return 0;
}
