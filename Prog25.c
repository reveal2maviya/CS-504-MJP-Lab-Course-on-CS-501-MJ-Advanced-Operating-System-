/*Write a C program that catches the ctrl-c (SIGINT) signal for the first time and display the appropriate message and exits on pressing ctrl-c again.*/
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

int ctrlCCount = 0; // Counter to keep track of Ctrl-C presses

// Signal handler for Ctrl-C (SIGINT)
void ctrlCHandler(int signum) {
    if (ctrlCCount == 0) {
        printf("Ctrl-C pressed. Press Ctrl-C again to exit.\n");
        ctrlCCount++;
    } else {
        printf("Ctrl-C pressed again. Exiting.\n");
        exit(EXIT_SUCCESS);
    }
}

int main() {
    // Set up the Ctrl-C signal handler
    signal(SIGINT, ctrlCHandler);

    // Keep the program running
    while (1) {
        // Program continues to run until Ctrl-C is pressed twice
    }

    return 0;
}
