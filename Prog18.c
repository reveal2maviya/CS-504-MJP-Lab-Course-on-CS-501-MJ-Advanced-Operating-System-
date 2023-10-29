/*Write a C program to demonstrates the different behaviour that can be seen with automatic, global, register, static and volatile variables (Use setjmp() and longjmp() system call).*/
#include <stdio.h>
#include <setjmp.h>

jmp_buf buffer; // Define a jump buffer

// Global variable
int global_var = 1;

void automatic_example() {
    int automatic_var = 2;
    printf("Automatic variable: %d\n", automatic_var);
}

void register_example() {
    register int register_var = 3;
    printf("Register variable: %d\n", register_var);
}

void static_example() {
    static int static_var = 4;
    printf("Static variable: %d\n", static_var);
}

void volatile_example() {
    volatile int volatile_var = 5;
    printf("Volatile variable: %d\n", volatile_var);
}

int main() {
    if (setjmp(buffer) != 0) {
        // This block is executed after longjmp
        printf("Returning to the main function\n");
        return 0;
    }

    printf("Global variable: %d\n", global_var);

    automatic_example();
    register_example();
    static_example();
    volatile_example();

    // Simulate a non-local jump
    longjmp(buffer, 1);

    // This code will not be reached
    printf("This will not be printed\n");

    return 0;
}
