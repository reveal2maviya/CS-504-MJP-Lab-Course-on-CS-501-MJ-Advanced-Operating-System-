/*Write a C program that illustrates suspending and resuming processes using signals.*/
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

volatile int suspended = 0; // Variable to track the process state

// Signal handler for SIGTSTP (Ctrl-Z)
void suspendHandler(int signum) {
    if (suspended) {
        printf("Resumed. PID: %d\n", getpid());
        suspended = 0;
    } else {
        printf("Suspended. PID: %d\n", getpid());
        suspended = 1;
    }
}

int main() {
    // Set up a signal handler for SIGTSTP
    signal(SIGTSTP, suspendHandler);

    printf("Running. PID: %d\n", getpid());

    while (1) {
        if (!suspended) {
            // Simulate some work in the process
            sleep(1);
        }
    }

    return 0;
}
