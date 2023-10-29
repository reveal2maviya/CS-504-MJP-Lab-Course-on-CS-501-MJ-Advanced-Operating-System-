/*Write a C program which create a child process which catch a signal sighup, sigint and sigquit. The Parent process send a sighup or sigint signal after every 3 seconds, at the end of 30 second parent send sigquit signal to child and child terminates my displaying message “My DADDY has Killed me!!!”.*/
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

volatile int child_pid = 0;
volatile int terminate_child = 0;

// Signal handler for child process
void childSignalHandler(int signum) {
    if (signum == SIGHUP) {
        printf("Child: Received SIGHUP signal\n");
    } else if (signum == SIGINT) {
        printf("Child: Received SIGINT signal\n");
    } else if (signum == SIGQUIT) {
        printf("Child: Received SIGQUIT signal. Terminating...\n");
        terminate_child = 1;
    }
}

int main() {
    pid_t pid;
    int child_status;

    pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) { // Child process
        // Set up signal handlers for child
        signal(SIGHUP, childSignalHandler);
        signal(SIGINT, childSignalHandler);
        signal(SIGQUIT, childSignalHandler);

        while (!terminate_child) {
            // Child continues running, handling signals
        }
        printf("My DADDY has Killed me!!!\n");
        exit(EXIT_SUCCESS);
    } else { // Parent process
        child_pid = pid;

        // Send SIGHUP signal to child every 3 seconds
        for (int i = 0; i < 10; i++) {
            sleep(3);
            kill(child_pid, SIGHUP);
        }

        // Send SIGINT signal to child every 3 seconds
        for (int i = 0; i < 10; i++) {
            sleep(3);
            kill(child_pid, SIGINT);
        }

        // Wait for a total of 30 seconds
        sleep(10);

        // Send SIGQUIT to terminate the child process
        kill(child_pid, SIGQUIT);

        // Wait for the child to terminate
        waitpid(child_pid, &child_status, 0);

        if (WIFEXITED(child_status)) {
            printf("Parent: Child terminated normally\n");
        } else {
            printf("Parent: Child terminated abnormally\n");
        }
    }

    return 0;
}
