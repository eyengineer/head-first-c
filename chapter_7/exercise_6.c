/*
 * ============================================================================
 * PURPOSE:
 * This program demonstrates how to create a "Variadic Function" in C.
 * A variadic function can accept an unlimited number of arguments (like printf).
 *
 * WHAT IT TEACHES:
 * 1. stdarg.h: The header required for variadic functions.
 * 2. Ellipsis (...): The syntax used to indicate variable arguments.
 * 3. va_list, va_start, va_arg, va_end: The macros used to process arguments.
 * ============================================================================
 */

#include <stdio.h>  // Required for printf()
#include <stdarg.h> // Required for va_list, va_start, va_arg, va_end

// ============================================================================
// VARIADIC FUNCTION
// ============================================================================
// 'int count': A fixed argument that tells the function how many extra arguments to expect.
// '...': The ellipsis. It tells the compiler that a variable number of arguments will follow.
void print_ints(int count, ...)
{
    // 1. Declare a 'va_list'. This is a special type that holds the state of the variable arguments.
    va_list ap;
    
    // 2. Initialize the list. 'va_start' takes two arguments:
    // - The va_list variable ('ap').
    // - The name of the LAST fixed argument ('count').
    // This tells C where the variable arguments start in memory.
    va_start(ap, count);
    
    int i; // Loop counter
    // 3. Loop 'count' times to read exactly that many arguments.
    for (i = 0; i < count; i++) {
        
        // 4. 'va_arg' fetches the next argument from the list.
        // It takes two arguments:
        // - The va_list variable ('ap').
        // - The TYPE of the argument we expect to read ('int').
        // It returns the value and automatically advances the list to the next argument.
        int val = va_arg(ap, int);
        
        // 5. Print the value. '%i' is for integers.
        printf("Argument %i: %i\n", i, val);
    }
    
    // 6. 'va_end' cleans up the list. 
    // It must be called before the function returns to free any resources used by va_list.
    va_end(ap);
}

// ============================================================================
// MAIN FUNCTION
// ============================================================================
int main()
{
    // Call the function.
    // The first argument (3) is the 'count' (fixed argument).
    // The next three arguments (79, 101, 32) are the variable arguments.
    // print_ints will loop 3 times and read those three integers.
    print_ints(3, 79, 101, 32); 
    
    return 0; // Indicate successful execution
}
