#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/times.h>

// Question: How to create "n" child processes and calculate the total cumulative time spent by the children in user and kernel mode in C?

// Instructions for Windows (Note: This program is primarily for Unix-like systems and may not work on Windows):
// 1. This program is designed for Unix-like systems and relies on POSIX-specific system calls.
// 2. To run on Windows, you may consider using a Unix-like environment or a tool like Cygwin or Windows Subsystem for Linux (WSL).
// 3. In a Unix-like environment, you can compile and run the program as follows:

// Instructions for Ubuntu (or other Linux-based systems):
// 1. Open a terminal.
// 2. Compile the C program using a C compiler, e.g., GCC:
//    Example: gcc program.c -o child_processes_time
// 3. Run the compiled program, providing the number of child processes (n) as an argument.
//    Example: ./child_processes_time 5

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <number_of_child_processes>\n", argv[0]);
        return 1;
    }

    int num_children = atoi(argv[1]);
    struct tms start_time, end_time;
    clock_t start_clock, end_clock;

    start_clock = times(&start_time);  // Record start time

    for (int i = 0; i < num_children; i++) {
        pid_t child_pid = fork();

        if (child_pid == -1) {
            perror("fork");
            return 1;
        } else if (child_pid == 0) {
            // Child process
            printf("Child process %d (PID %d) is running...\n", i + 1, getpid());
            exit(0);
        }
    }

    for (int i = 0; i < num_children; i++) {
        wait(NULL);  // Wait for all child processes to finish
    }

    end_clock = times(&end_time);  // Record end time

    printf("Total User Time: %f seconds\n", (double)(end_time.tms_utime - start_time.tms_utime) / sysconf(_SC_CLK_TCK));
    printf("Total System Time: %f seconds\n", (double)(end_time.tms_stime - start_time.tms_stime) / sysconf(_SC_CLK_TCK));

    return 0;
}
