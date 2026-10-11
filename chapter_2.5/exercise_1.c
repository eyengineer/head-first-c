/*
 * PURPOSE:
 * This code is a "mini search engine" that demonstrates how to combine
 * arrays, strings, pointers, and functions in C.
 *
 * WHAT IT TEACHES:
 * 1.  Global 2D Arrays: How to declare an array of strings outside main() 
 *     so all functions can access it.
 * 2.  String Searching (strstr): How to find a substring inside a larger string.
 * 3.  Safe Input (fgets): How to read user input without causing a buffer overflow.
 * 4.  Function Order: Why functions must be defined before they are called.
 * 5.  Array Decay: How arrays automatically become pointers when passed to functions.
 */

// Include the standard input/output library for printf, fgets, etc.
#include <stdio.h>

// Include the string library to use the strstr() function for searching
#include <string.h>

// Declare a 2D array to store 5 song names, each up to 80 characters
// It is declared globally so both find_track() and main() can access it
char tracks[][80] = {
    "I left my heart in Harvard Med School",
    "Newark, Newark - a wonderful town",
    "Dancing with a Dork",
    "From here to maternity",
    "The girl from Iwo Jima",
};

// Function to search for a keyword in the song list
// Takes a string (search term) as an argument
void find_track(char search_for[])
{
    int i;
    // Loop through all 5 songs in the tracks array
    for (i = 0; i < 5; i++) {
        // strstr checks if search_for exists inside tracks[i]
        // If found, it returns a pointer to the match (truthy), otherwise NULL (falsy)
        if (strstr(tracks[i], search_for))
            // Print the index number and the full song name
            printf("Track %i: '%s'\n", i, tracks[i]);
    }
}

// The entry point of the program
int main()
{
    // Declare a character array to store the user's search input (max 80 chars)
    char search_for[80];

    // Prompt the user to enter a search term
    printf("Search for: ");

    // Read the user's input safely using fgets (prevents buffer overflow)
    // It reads up to 80 characters from standard input (keyboard)
    fgets(search_for, 80, stdin);
    
    // Remove the newline character (\n) from the input
    // This is necessary because fgets keeps the Enter key press
    search_for[strcspn(search_for, "\n")] = '\0';
    // Call the find_track function, passing the user's search term
    find_track(search_for);

    // Return 0 to indicate successful program execution
    return 0;
}
