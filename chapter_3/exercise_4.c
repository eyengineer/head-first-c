/*
 * PURPOSE:
 * This program reads words from standard input and splits them into two separate files.
 * Odd-numbered words go to Standard Output (stdout), and even-numbered words go to 
 * Standard Error (stderr). It demonstrates how to redirect data streams using the command line.
 *
 * WHAT IT TEACHES:
 * 1. Stream Redirection: Using '>' to redirect stdout and '2>' to redirect stderr.
 * 2. Modulo Operator (%): Using i % 2 to determine if a counter is odd or even.
 * 3. Reading Words: Using scanf("%9s", word) to read words without spaces.
 * 4. Stream Separation: Directing different types of output to different destinations.
 */

#include <stdio.h>

int main()
{
    // Array to store each word read from the input (max 9 chars + null terminator)
    char word[10];
    
    // Counter to track the position of the word (1st, 2nd, 3rd, etc.)
    int i = 0;

    // Read a word from standard input (keyboard or file)
    // %9s reads a string of up to 9 characters, preventing buffer overflow
    // The loop continues as long as exactly 1 word is successfully read
    while (scanf("%9s", word) == 1) {
        
        // Increment the counter for each new word
        i = i + 1;

        // Check if the word's position is odd (1st, 3rd, 5th...)
        // i % 2 returns the remainder of division by 2. If it's 1, the number is odd.
        if (i % 2) {
            // If odd, print the word to Standard Output (stdout)
            // By default, this goes to the screen, but can be redirected with '>'
            fprintf(stdout, "%s\n", word);
        } else {
            // If even, print the word to Standard Error (stderr)
            // By default, this goes to the screen, but can be redirected with '2>'
            fprintf(stderr, "%s\n", word);
        }
    }

    // Return 0 to indicate successful program execution
    return 0;
}
