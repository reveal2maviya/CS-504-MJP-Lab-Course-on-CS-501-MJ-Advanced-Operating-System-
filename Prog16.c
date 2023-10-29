/*Handle the two-way communication between parent and child processes using pipe*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main() {
    int pipe_from_parent_to_child[2]; // Pipe for parent to child
    int pipe_from_child_to_parent[2]; // Pipe for child to parent
    pid_t child_pid;

    // Create the pipe for parent to child
    if (pipe(pipe_from_parent_to_child) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Create the pipe for child to parent
    if (pipe(pipe_from_child_to_parent) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Create a child process
    child_pid = fork();

    if (child_pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (child_pid == 0) { // Child process
        close(pipe_from_parent_to_child[1]); // Close the write end (from parent)
        close(pipe_from_child_to_parent[0]); // Close the read end (to parent)

        char buffer[100];
        ssize_t num_bytes;

        // Read from the pipe (from parent)
        num_bytes = read(pipe_from_parent_to_child[0], buffer, sizeof(buffer));
        if (num_bytes == -1) {
            perror("read (from parent)");
            exit(EXIT_FAILURE);
        }

        // Null-terminate the string
        buffer[num_bytes] = '\0';

        printf("Child process received from parent: %s\n", buffer);

        const char *message_to_parent = "Hello from child!";
        
        // Write to the pipe (to parent)
        if (write(pipe_from_child_to_parent[1], message_to_parent, strlen(message_to_parent)) == -1) {
            perror("write (to parent)");
            exit(EXIT_FAILURE);
        }

        close(pipe_from_parent_to_child[0]); // Close the read end (from parent)
        close(pipe_from_child_to_parent[1]); // Close the write end (to parent)
    } else { // Parent process
        close(pipe_from_parent_to_child[0]); // Close the read end (to child)
        close(pipe_from_child_to_parent[1]); // Close the write end (from child)

        const char *message_to_child = "Hello from parent!";
        
        // Write to the pipe (to child)
        if (write(pipe_from_parent_to_child[1], message_to_child, strlen(message_to_child)) == -1) {
            perror("write (to child)");
            exit(EXIT_FAILURE);
        }

        char buffer[100];
        ssize_t num_bytes;

        // Read from the pipe (from child)
        num_bytes = read(pipe_from_child_to_parent[0], buffer, sizeof(buffer));
        if (num_bytes == -1) {
            perror("read (from child)");
            exit(EXIT_FAILURE);
        }

        // Null-terminate the string
        buffer[num_bytes] = '\0';

        printf("Parent process received from child: %s\n", buffer);

        close(pipe_from_parent_to_child[1]); // Close the write end (to child)
        close(pipe_from_child_to_parent[0]); // Close the read end (from child)
    }

    return 0;
}
