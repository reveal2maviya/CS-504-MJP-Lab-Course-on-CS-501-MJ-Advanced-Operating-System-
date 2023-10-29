#include <stdio.h>
#include <setjmp.h>

// Question: How to demonstrate the different behavior of automatic, global, register, static, and volatile variables using `setjmp()` and `longjmp()` in C?

// Instructions for Windows (Note: This program is primarily for Unix-like systems and may not work on Windows):
// 1. This program is designed for Unix-like systems and relies on POSIX-specific system calls.
// 2. To run on Windows, you may consider using a Unix-like environment or a tool like Cygwin or Windows Subsystem for Linux (WSL).
// 3. In a Unix-like environment, you can compile and run the program as follows:

// Instructions for Ubuntu (or other Linux-based systems):
// 1. Open a terminal.
// 2. Compile the C program using a C compiler, e.g., GCC:
//    Example: gcc program.c -o variable_behavior_example
// 3. Run the compiled program:
//    Example: ./variable_behavior_example

jmp_buf jump_buffer;

void demonstrate_variable_behavior() {
    int automatic_var = 10;
    static int static_var = 20;
    volatile int volatile_var = 30;
    register int register_var = 40;
    int global_var = 50;

    printf("Inside demonstrate_variable_behavior():\n");
    printf("Automatic Variable: %d\n", automatic_var);
    printf("Static Variable: %d\n", static_var);
    printf("Volatile Variable: %d\n", volatile_var);
    printf("Register Variable: %d\n", register_var);
    printf("Global Variable: %d\n", global_var);

    longjmp(jump_buffer, 1);  // Jump back to main()
}

int main() {
    int result = setjmp(jump_buffer);

    if (result == 0) {
        // Initial execution
        demonstrate_variable_behavior();
    } else {
        // After longjmp, this code is executed
        printf("\nInside main() after longjmp:\n");
    }

    // Accessing variables declared in demonstrate_variable_behavior() is not safe here

    return 0;
}
