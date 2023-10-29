/*Write a C program to get and set the resource limits such as files, memory associated with a process*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>

int main() {
    struct rlimit rlim;

    // Get the current resource limit for maximum stack size
    if (getrlimit(RLIMIT_STACK, &rlim) == 0) {
        printf("Current stack size limit: soft=%lu, hard=%lu\n", (unsigned long)rlim.rlim_cur, (unsigned long)rlim.rlim_max);
    } else {
        perror("getrlimit");
        exit(EXIT_FAILURE);
    }

    // Set a new stack size limit
    rlim.rlim_cur = 1024 * 1024;  // Set the soft limit to 1MB
    rlim.rlim_max = 2048 * 1024;  // Set the hard limit to 2MB

    if (setrlimit(RLIMIT_STACK, &rlim) == 0) {
        printf("New stack size limit: soft=%lu, hard=%lu\n", (unsigned long)rlim.rlim_cur, (unsigned long)rlim.rlim_max);
    } else {
        perror("setrlimit");
        exit(EXIT_FAILURE);
    }

    // Attempt to exceed the new stack size limit
    // This will trigger a segmentation fault if the limit is reached
    char buffer[1024 * 1024]; // Allocate 1MB of stack memory

    return 0;
}
