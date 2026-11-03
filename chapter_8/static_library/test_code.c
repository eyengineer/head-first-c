/*
 * PURPOSE:
 * This is the main test program. It uses the 'security library' we just created.
 * It encrypts a string, prints it, checks its checksum, then decrypts it.
 */

#include <stdio.h>
#include "encrypt.h"  // Use double quotes for local files!
#include "checksum.h" // Use double quotes for local files!

int main()
{
    // The secret message
    char s[] = "Speak friend and enter";
    
    // 1. Call the encrypt function from encrypt.c
    encrypt(s);
    printf("Encrypted to '%s'\n", s);
    
    // 2. Call the checksum function from checksum.c
    printf("Checksum is %i\n", checksum(s));
    
    // 3. Call encrypt AGAIN. Because XOR is reversible, it decrypts the string!
    encrypt(s);
    printf("Decrypted back to '%s'\n", s);
    printf("Checksum is %i\n", checksum(s));
    
    return 0;
}
