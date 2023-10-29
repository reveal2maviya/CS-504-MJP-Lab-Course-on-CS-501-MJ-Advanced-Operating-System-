#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/resource.h>

// Question: How to get and set resource limits, such as the maximum number of open files and memory, associated with a process in C?

// Instructions for Windows (Note: This program is primarily for Unix-like systems and may not work on Windows):
// 1. This program is designed for Unix-like systems and relies on POSIX-specific system calls.
// 2. To run on Windows, you may consider using a Unix-like environment or a tool like Cygwin or Windows Subsystem for Linux (WSL).
// 3. In a Unix-like environment, you can compile and run the program as follows:

// Instructions for Ubuntu (or other Linux-based systems):
// 1. Open a terminal.
// 2. Compile the C program using a C compiler, e.g., GCC:
//    Example: gcc program.c -o resource_limits_example
// 3. Run the compiled program.

int main() {
    struct rlimit limit;
    
    // Get and display the current maximum number of open files (soft limit)
    if (getrlimit(RLIMIT_NOFILE, &limit) == 0) {
        printf("Current Maximum Number of Open Files (soft limit): %lu\n", limit.rlim_cur);
    } else {
        perror("getrlimit");
        return 1;
    }

    // Set a new maximum number of open files (soft limit) to 10000
    limit.rlim_cur = 10000;
    if (setrlimit(RLIMIT_NOFILE, &limit) == 0) {
        printf("New Maximum Number of Open Files (soft limit): %lu\n", limit.rlim_cur);
    } else {
        perror("setrlimit");
        return 1;
    }

    // Get and display the maximum memory size (soft limit)
    if (getrlimit(RLIMIT_AS, &limit) == 0) {
        printf("Current Maximum Memory Size (soft limit): %lu\n", limit.rlim_cur);
    } else {
        perror("getrlimit");
        return 1;
    }

    // Set a new maximum memory size (soft limit) to 512MB
    limit.rlim_cur = 512 * 1024 * 1024;
    if (setrlimit(RLIMIT_AS, &limit) == 0) {
        printf("New Maximum Memory Size (soft limit): %lu\n", limit.rlim_cur);
    } else {
        perror("setrlimit");
        return 1;
    }

    return 0;
}
