/*Write a C program to create „n‟ child processes. When all „n‟ child processes terminates, Display total cumulative time children spent in user and kernel mode.*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/resource.h>
#include <unistd.h>

int main() {
    int n = 5; // Number of child processes
    int i;
    struct rusage usage;
    struct timeval user_time, kernel_time;
    long total_user_seconds = 0, total_kernel_seconds = 0;

    for (i = 0; i < n; i++) {
        pid_t child_pid = fork();

        if (child_pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (child_pid == 0) { // Child process
            // Simulate some work in the child process
            for (int j = 0; j < 100000000; j++) {
                // Do some computation
            }
            exit(EXIT_SUCCESS);
        }
    }

    // Parent process waits for all child processes to terminate
    for (i = 0; i < n; i++) {
        int status;
        pid_t terminated_pid = wait(&status);

        if (terminated_pid != -1) {
            // Get resource usage for the terminated child process
            getrusage(RUSAGE_CHILDREN, &usage);

            // Accumulate user and kernel times
            user_time = usage.ru_utime;
            kernel_time = usage.ru_stime;
            total_user_seconds += user_time.tv_sec;
            total_kernel_seconds += kernel_time.tv_sec;
        }
    }

    printf("Total cumulative time spent in user mode: %ld seconds\n", total_user_seconds);
    printf("Total cumulative time spent in kernel mode: %ld seconds\n", total_kernel_seconds);

    return 0;
}
