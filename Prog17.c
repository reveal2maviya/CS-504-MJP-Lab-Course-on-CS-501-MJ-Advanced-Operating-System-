/*Demonstrate the use of atexit() function.*/
#include <stdio.h>
#include <stdlib.h>

void cleanup1() {
    printf("Cleanup function 1 called.\n");
}

void cleanup2() {
    printf("Cleanup function 2 called.\n");
}

int main() {
    // Register cleanup functions using atexit
    if (atexit(cleanup1) != 0) {
        perror("Failed to register cleanup function 1");
        return 1;
    }

    if (atexit(cleanup2) != 0) {
        perror("Failed to register cleanup function 2");
        return 1;
    }

    printf("Main function executing.\n");

    // Exiting the program

    return 0;
}
