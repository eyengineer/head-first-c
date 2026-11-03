/*
 * PURPOSE:
 * Calculates a simple checksum (a numerical summary) of a string.
 * It's used to check if the data has been modified.
 */

#include "checksum.h"

int checksum(char *message)
{
    int c = 0; // Initialize the checksum value
    
    // Loop through each character of the string
    while (*message) {
        
        // XOR the current checksum with the current character, then add to 'c'
        // This creates a unique number based on the string's contents
        c += c ^ (int)(*message); 
        
        // Move to the next character
        message++;
    }
    
    return c; // Return the final calculated checksum
}
