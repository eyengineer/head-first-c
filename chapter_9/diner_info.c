/*
 * ============================================================================
 * PURPOSE:
 * This program demonstrates how to read environment variables using getenv().
 * It prints the first command-line argument (number of diners) and the 
 * value of the "JUICE" environment variable.
 *
 * WHAT IT TEACHES:
 * 1. Environment Variables: Variables set by the OS or the user before the program runs.
 * 2. getenv(): A function that searches for a specific environment variable and returns its value.
 * ============================================================================
 */

#include <stdio.h>
#include <stdlib.h> // Required for getenv()

int main(int argc, char *argv[])
{
    // 1. Print the first command-line argument.
    // If the program is run as "./diner_info 4", argv[1] is "4".
    printf("Diners: %s\n", argv[1]);
    
    // 2. getenv("JUICE") searches the environment for a variable named "JUICE".
    // If found, it returns a pointer to its value (e.g., "peach and apple").
    // If not found, it returns NULL. %s handles both cases (prints the string or "(null)").
    printf("Juice: %s\n", getenv("JUICE"));
    
    return 0; // Exit successfully
}
