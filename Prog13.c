/*Write a C program that redirects standard output to a file output.txt. (use of dup and open system call).*/
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    // Open the file "output.txt" for writing
    int fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    
    if (fd == -1) {
        perror("Unable to open the file");
        return 1;
    }

    // Duplicate the file descriptor to stdout (file descriptor 1)
    if (dup2(fd, 1) == -1) {
        perror("Unable to redirect stdout");
        return 1;
    }

    // Now, stdout is redirected to the "output.txt" file
    printf("This is redirected to a file using dup and open system calls.\n");

    // Close the file descriptor
    close(fd);

    return 0;
}
