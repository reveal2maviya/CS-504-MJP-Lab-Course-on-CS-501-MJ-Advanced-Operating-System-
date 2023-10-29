/*Write a C program which creates a child process and child process catches a signal SIGHUP, SIGINT and SIGQUIT. The Parent process send a SIGHUP or SIGINT signal after every 3 seconds, at the end of 15 second parent send SIGQUIT signal to child and child terminates by displaying message "My Papa has Killed me!!!”.*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

volatile int child_pid = 0;

// Signal handler for child process
void childSignalHandler(int signum) {
    if (signum == SIGHUP) {
        printf("Child: Received SIGHUP signal\n");
    } else if (signum == SIGINT) {
        printf("Child: Received SIGINT signal\n");
    }
}

int main() {
    pid_t pid;
    int childStatus;

    pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) { // Child process
        // Set up signal handlers for child
        signal(SIGHUP, childSignalHandler);
        signal(SIGINT, childSignalHandler);

        while (1) {
            // Child continues running, handling signals
        }
    } else { // Parent process
        child_pid = pid;

        // Send SIGHUP signal to child every 3 seconds
        for (int i = 0; i < 5; i++) {
            sleep(3);
            kill(child_pid, SIGHUP);
        }

        // Send SIGINT signal to child every 3 seconds
        for (int i = 0; i < 5; i++) {
            sleep(3);
            kill(child_pid, SIGINT);
        }

        // Wait for a total of 15 seconds
        sleep(5);

        // Send SIGQUIT to terminate the child process
        kill(child_pid, SIGQUIT);

        // Wait for the child to terminate
        waitpid(child_pid, &childStatus, 0);

        if (WIFEXITED(childStatus)) {
            printf("Parent: Child terminated normally\n");
        } else {
            printf("Parent: Child terminated abnormally\n");
        }
    }

    return 0;
}
