/*
 * PURPOSE:
 * This program demonstrates how to create multiple test functions (filters) 
 * and pass them to a single 'find' function using Function Pointers.
 * It allows the same 'find' logic to be reused for completely different searches.
 *
 * WHAT IT TEACHES:
 * 1. Function Pointer Syntax: How to declare and pass function pointers.
 * 2. Reusability: Writing one generic function that behaves differently based on the callback.
 * 3. Logical Operators: Using && (AND) and || (OR) to build complex string search criteria.
 */

#include <stdio.h>
#include <string.h>

#define NUM_ADS 7

// The data we are searching through (array of string pointers)
char *ADS[] = {
    "William: SBM GSOH likes sports, TV, dining",
    "Matt: SWM NS likes art, movies, theater",
    "Luis: SLM ND likes books, theater, art",
    "Mike: DWM DS likes trucks, sports and bieber",
    "Peter: SAM likes chess, working out and art",
    "Josh: SJM likes sports, movies and theater",
    "Jed: DBM likes theater, books and dining"
};

// ============================================================================
// TEST FUNCTIONS (The Filters)
// Each function returns 1 (true) if the ad matches the criteria, 0 (false) otherwise.
// ============================================================================

// Filter 1: 
// - strstr(s, "sports") checks if "sports" exists (returns pointer if true).
// - !strstr(s, "bieber") checks if "bieber" DOES NOT exist (! inverts the result).
// - && (Logical AND) means BOTH conditions must be true for the whole expression to be true.
// Result: Only matches ads that have sports AND do NOT have bieber.
int sports_no_bieber(char *s) {
    return strstr(s, "sports") && !strstr(s, "bieber");
}

// Filter 2: 
// - strstr(s, "sports") checks for sports.
// - || (Logical OR) means if EITHER the left side OR the right side is true, return true.
// - strstr(s, "working out") checks for working out.
// Result: Matches if the ad has sports OR working out (or both).
int sports_or_workout(char *s) {
    return strstr(s, "sports") || strstr(s, "working out");
}

// Filter 3: 
// - strstr(s, "NS") checks for "NS" (Non-Smoker).
// - && (Logical AND) requires both "NS" and "theater" to be present.
// Result: Matches only non-smokers who also like theater.
int ns_theater(char *s) {
    return strstr(s, "NS") && strstr(s, "theater");
}

// Filter 4: 
// - Uses multiple || (OR) operators. 
// - If it has "arts", OR "theater", OR "dining", the condition is true.
// Result: Matches anyone interested in arts, theater, or dining.
int arts_theater_or_dining(char *s) {
    return strstr(s, "arts") || strstr(s, "theater") || strstr(s, "dining");
}

// ============================================================================
// THE FIND FUNCTION (The "Testing Machine")
// ============================================================================
// Parameter: int (*match)(char *)
// - 'match' is the name of our function pointer.
// - It points to a function that takes a 'char *' and returns an 'int'.
// This allows 'find' to call ANY function that has this exact signature.
void find(int (*match)(char *)) 
{
    int i;
    puts("Search results:");
    puts("----------------------------------------");

    // Loop through every ad in the array
    for (i = 0; i < NUM_ADS; i++) {
        
        // 'match' is called like a normal function.
        // - We pass the current ad (ADS[i]).
        // - If the filter function returns 1 (true), the if statement executes.
        if (match(ADS[i])) {
            printf("%s\n", ADS[i]);
        }
    }
    puts("----------------------------------------");
}

// ============================================================================
// MAIN FUNCTION
// ============================================================================
int main()
{
    // When passing a function as an argument, use the function name WITHOUT parentheses.
    // The function name acts as a memory address (pointer) to the function's code.
    // 'find' will use this address to call the function at the right time.
    
    printf("--- find(sports_no_bieber) ---\n");
    find(sports_no_bieber);
    
    printf("\n--- find(sports_or_workout) ---\n");
    find(sports_or_workout);
    
    printf("\n--- find(ns_theater) ---\n");
    find(ns_theater);
    
    printf("\n--- find(arts_theater_or_dining) ---\n");
    find(arts_theater_or_dining);
    
    return 0;
}
