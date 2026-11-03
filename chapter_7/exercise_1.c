/*
 * PURPOSE:
 * This program filters an array of personal ads. 
 * It searches for ads containing the word "sports" but NOT containing the word "bieber".
 * It demonstrates how to use string functions (strstr) and logical operators (&&, !) to filter data.
 *
 * WHAT IT TEACHES:
 * 1. strstr(): Finding a substring within a string.
 * 2. Logical NOT (!): Inverting a boolean result.
 * 3. Logical AND (&&): Requiring two conditions to be true at the same time.
 */

#include <stdio.h>
#include <string.h> // Required for strstr()

// Define the number of ads
#define NUM_ADS 7

// Declare and initialize an array of string pointers (the ads)
char *ADS[] = {
    "William: SBM GSOH likes sports, TV, dining",
    "Matt: SWM NS likes art, movies, theater",
    "Luis: SLM ND likes books, theater, art",
    "Mike: DWM DS likes trucks, sports and bieber",
    "Peter: SAM likes chess, working out and art",
    "Josh: SJM likes sports, movies and theater",
    "Jed: DBM likes theater, books and dining"
};

// Function to find and print the matching ads
void find()
{
    int i;
    puts("Search results:");
    puts("----------------------------------------");

    // Loop through each ad in the array
    for (i = 0; i < NUM_ADS; i++) {
        
        // The condition has two parts connected by && (AND):
        // 1. strstr(ADS[i], "sports"): Returns a pointer (true) if "sports" is found.
        // 2. ! strstr(ADS[i], "bieber"): The ! (NOT) inverts the result. 
        //    If "bieber" is NOT found, strstr returns NULL (false). !NULL becomes true.
        // So, the ad must have "sports" AND must NOT have "bieber".
        if ( strstr(ADS[i], "sports") && ! strstr(ADS[i], "bieber") ) {
            
            // If both conditions are true, print the ad
            printf("%s\n", ADS[i]);
        }
    }
    puts("----------------------------------------");
}

int main()
{
    // Call the function to start the search
    find();
    return 0;
}
