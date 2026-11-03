/*
 * PURPOSE:
 * This program demonstrates the power of Function Pointers.
 * It shows how to pass a function as an argument to another function, 
 * making the 'find' function completely reusable for any search criteria 
 * without duplicating the loop and print logic.
 *
 * WHAT IT TEACHES:
 * 1. Function Pointers: Treating functions as variables (storing their memory addresses).
 * 2. Callbacks: Passing a function to another function to be "called back" later.
 * 3. Abstraction: Separating the "testing logic" from the "iteration logic".
 */

#include <stdio.h>
#include <string.h> // Required for strstr()

#define NUM_ADS 3

// The array of strings (our data)
char *ADS[] = {
    "William likes sports and TV",
    "Mike likes sports and bieber",
    "Luis likes books and theater"
};

// ============================================================================
// TEST FUNCTIONS (The "Filters" / Callbacks)
// ============================================================================
// These functions return 1 (true) if the ad matches the criteria, 0 (false) otherwise.
// They act as the "matching rules" that we will pass to the find() function.

// Criteria 1: The ad MUST contain "sports" AND MUST NOT contain "bieber".
// strstr() returns a pointer (truthy) if found, or NULL (falsy) if not found.
// The ! (NOT) operator flips the truth value of the second strstr().
int sports_no_bieber(char *s) {
    return strstr(s, "sports") && !strstr(s, "bieber");
}

// Criteria 2: The ad MUST contain "books" OR MUST contain "theater".
// The || (OR) operator returns true if EITHER condition is true.
int arts_theater_or_dining(char *s) {
    return strstr(s, "books") || strstr(s, "theater");
}

// ============================================================================
// THE FIND FUNCTION (The "Testing Machine")
// ============================================================================
// This is the core function. It takes ONE parameter: 'match'.
// 'match' is a FUNCTION POINTER. It expects a function that:
// - Takes a single 'char *' (the string to test) as input.
// - Returns an 'int' (1 for true, 0 for false).
void find(int (*match)(char *)) 
{
    int i;
    puts("Search results:");
    
    // Loop through every ad in the array
    for (i = 0; i < NUM_ADS; i++) {
        
        // THE MAGIC LINE:
        // We use the function pointer 'match' just like a normal function name.
        // We pass the current ad (ADS[i]) to the function that 'match' points to.
        // If that function returns 1 (true), the condition is met.
        if (match(ADS[i])) {
            printf("%s\n", ADS[i]);
        }
    }
    puts("--------------------");
}

// ============================================================================
// MAIN FUNCTION
// ============================================================================
int main()
{
    // 1. Pass the NAME of the function 'sports_no_bieber'. 
    // In C, the name of a function is actually a pointer to its memory address.
    // find() will use this address to call it.
    printf("--- Searching for sports (no bieber) ---\n");
    find(sports_no_bieber);
    
    // 2. Pass the NAME of a different function.
    // The SAME find() function is reused, but it behaves completely differently.
    printf("\n--- Searching for arts/theater ---\n");
    find(arts_theater_or_dining);
    
    return 0;
}
