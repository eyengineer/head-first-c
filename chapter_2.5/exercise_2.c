/*
 * PURPOSE:
 * This code demonstrates how to print a string in reverse order using pointers.
 * It shows how to manipulate memory addresses directly instead of using array indices.
 *
 * WHAT IT TEACHES:
 * 1. Pointer Arithmetic: Moving a pointer backward through memory (t = t - 1).
 * 2. String Length (strlen): Finding the number of characters in a string.
 * 3. Pointer Comparison: Using while (t >= s) to loop until the start of the string.
 * 4. Dereferencing: Using *t to access the character at the current pointer position.
 */

// Include the standard input/output library for printf and puts
#include <stdio.h>
// Include the string library for strlen
#include <string.h>

// Function to print a string in reverse
// Takes a pointer to a character (the string) as an argument
void print_reverse(char *s)
{
    // Find the length of the string (excluding the null terminator)
    size_t len = strlen(s);

    // Initialize a pointer 't' to point to the last character of the string
    // s + len would point to the null terminator, so we subtract 1
    char *t = s + len - 1;

    // Loop backward from the last character to the first character
    // 's' is the start address, 't' is the current address
    while (t >= s) {
        // Print the character currently pointed to by 't'
        printf("%c", *t);

        // Move the pointer one step backward in memory (pointer arithmetic)
        t = t - 1;
    }

    // Print a newline at the end
    puts("");
}

// The entry point of the program
int main()
{
    // Declare and initialize a string
    char str[] = "Hello";

    // Call the function to print the string in reverse
    print_reverse(str);

    // Return 0 to indicate successful program execution
    return 0;
}
