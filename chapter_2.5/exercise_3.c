/*
 * PURPOSE:
 * This code creates a crossword puzzle using an array of pointers (char *juices[]).
 * It demonstrates how to store a list of strings efficiently using pointers,
 * how to swap pointers, and how to use pointer arithmetic to access elements.
 *
 * WHAT IT TEACHES:
 * 1. Array of Pointers: Storing strings as pointers instead of fixed-size arrays.
 * 2. Pointer Swapping: Swapping addresses (not data) to reorder strings.
 * 3. Pointer Arithmetic: Calculating indices like (18 + 7) / 5.
 * 4. String Reversal: Using the print_reverse() function to print strings backward.
 */

// Include the standard input/output library for printf and puts
#include <stdio.h>
// Include the string library for strlen (used in print_reverse)
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
    while (t >= s) {
        // Print the character currently pointed to by 't'
        printf("%c", *t);

        // Move the pointer one step backward in memory
        t = t - 1;
    }

    // Print a newline at the end
    puts("");
}

// The entry point of the program
int main()
{
    // Declare an array of pointers to strings
    // Each element is a pointer to a string literal
    char *juices[] = {
        "dragonfruit", "waterberry", "sharonfruit", "uglifruit",
        "rumberry", "kiwifruit", "mulberry", "strawberry",
        "blueberry", "blackberry", "starfruit"
    };

    // Declare a temporary pointer for swapping
    char *a;

    // Across 1: Print the 7th element (index 6) -> "mulberry"
    puts(juices[6]);

    // Across 2: Print the 8th element (index 7) in reverse -> "yrrebwarts"
    print_reverse(juices[7]);

    // Across 3: Swap pointers to reorder strings
    // Save the pointer at index 2 ("sharonfruit") into 'a'
    a = juices[2];
    // Put the pointer at index 8 ("blueberry") into index 2
    juices[2] = juices[8];
    // Put the saved pointer (originally index 2) into index 8
    juices[8] = a;

    // Across 3: Print the new element at index 8 -> "sharonfruit"
    puts(juices[8]);

    // Across 4: Calculate index (18 + 7) / 5 = 25 / 5 = 5
    // Print the 6th element (index 5) in reverse -> "tiurifiwek"
    print_reverse(juices[(18 + 7) / 5]);

    // Down 5: Print the 3rd element (index 2) -> now "blueberry" (after swap)
    puts(juices[2]);

    // Down 6: Print the 10th element (index 9) in reverse -> "yrrebnac"
    print_reverse(juices[9]);

    // Down 6 (continued): Swap pointers
    // Put index 3 ("uglifruit") into index 1 ("waterberry" becomes "uglifruit")
    juices[1] = juices[3];

    // Down 7: Print the 11th element (index 10) -> "starfruit"
    puts(juices[10]);

    // Down 8: Print the 2nd element (index 1) in reverse -> "tiurifugu"
    print_reverse(juices[1]);

    // Return 0 to indicate successful program execution
    return 0;
}

