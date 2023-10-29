/*Write a C program to send SIGALRM signal by child process to parent process and parent process make a provision to catch the signal and display alarm is fired.(Use Kill, fork, signal and sleep system call)*/
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

volatile int alarm_fired = 0;

// Signal handler for SIGALRM
void alarmHandler(int signum) {
    alarm_fired = 1;
    printf("Parent: Alarm is fired!\n");
}

int main() {
    pid_t child_pid;
    int child_status;

    child_pid = fork();

    if (child_pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (child_pid == 0) { // Child process
        // Sleep for 5 seconds and then send SIGALRM to the parent
        sleep(5);
        kill(getppid(), SIGALRM);
        exit(EXIT_SUCCESS);
    } else { // Parent process
        // Set up a signal handler for SIGALRM
        signal(SIGALRM, alarmHandler);

        printf("Parent: Waiting for alarm...\n");

        // Wait for the child to terminate
        wait(&child_status);

        if (WIFEXITED(child_status)) {
            printf("Parent: Child terminated normally\n");
        } else {
            printf("Parent: Child terminated abnormally\n");
        }

        // Check if the alarm was fired
        if (alarm_fired) {
            printf("Parent: Caught the alarm!\n");
        }
    }

    return 0;
}
