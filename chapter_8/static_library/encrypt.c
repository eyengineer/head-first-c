/*
 * PURPOSE:
 * This file contains the actual logic for the encrypt function.
 * It uses the XOR operator (^) to scramble the text.
 */

#include "encrypt.h" // Include our own header file to ensure signature matches

void encrypt(char *message)
{
    // Loop through the string until we hit the null terminator ('\0')
    while (*message) {
        
        // XOR the character with the number 31. 
        // XOR is reversible: if you do it twice, you get the original character back!
        *message = *message ^ 31; 
        
        // Move the pointer to the next character in the string
        message++; 
    }
}
