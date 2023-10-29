#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

// Signal handler function to block signals
void block_signals(int signum) {
    printf("Signal %d received but blocked.\n", signum);
}

// Question: How to create a C program that implements the Unix/Linux command "ls -l | wc -l" using fork, pipe, and exec system calls while blocking Ctrl-C and Ctrl-\ signals during execution?

// Instructions for Windows (Note: This program is primarily for Unix-like systems and may not work on Windows):
// 1. This program is designed for Unix-like systems and relies on POSIX-specific system calls.
// 2. To run on Windows, you may consider using a Unix-like environment or a tool like Cygwin or Windows Subsystem for Linux (WSL).
// 3. In a Unix-like environment, you can compile and run the program as follows:

// Instructions for Ubuntu (or other Linux-based systems):
// 1. Open a terminal.
// 2. Compile the C program using a C compiler, e.g., GCC:
//    Example: gcc program.c -o ls_wc_example
// 3. Run the compiled program.
// 4. The program will execute the "ls -l | wc -l" command while blocking Ctrl-C and Ctrl-\ signals.

int main() {
    // Block Ctrl-C and Ctrl-\ signals
    signal(SIGINT, block_signals);
    signal(SIGQUIT, block_signals);

    int pipe_fd[2];
    pid_t ls_pid, wc_pid;

    if (pipe(pipe_fd) == -1) {
        perror("pipe");
        return 1;
    }

    if ((ls_pid = fork()) == -1) {
        perror("fork");
        return 1;
    }

    if (ls_pid == 0) {
        // Child process for "ls -l"
        close(pipe_fd[0]);  // Close read end
        dup2(pipe_fd[1], STDOUT_FILENO);  // Redirect standard output to the write end of the pipe
        close(pipe_fd[1]);  // Close the original write end

        execlp("ls", "ls", "-l", NULL);
        perror("execlp ls");
        exit(1);
    } else {
        if ((wc_pid = fork()) == -1) {
            perror("fork");
            return 1;
        }

        if (wc_pid == 0) {
            // Child process for "wc -l"
            close(pipe_fd[1]);  // Close write end
            dup2(pipe_fd[0], STDIN_FILENO);  // Redirect standard input to the read end of the pipe
            close(pipe_fd[0]);  // Close the original read end

            execlp("wc", "wc", "-l", NULL);
            perror("execlp wc");
            exit(1);
        } else {
            // Parent process
            close(pipe_fd[0]);  // Close read end
            close(pipe_fd[1]);  // Close write end

            waitpid(ls_pid, NULL, 0);
            waitpid(wc_pid, NULL, 0);
        }
    }

    return 0;
}
