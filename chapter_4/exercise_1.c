/*
 * PURPOSE:
 * This program simulates a restaurant bill calculator. It reads prices one by one, 
 * calculates the total with sales tax, and prints a running total and final bill.
 *
 * WHAT IT TEACHES:
 * 1. Choosing Correct Data Types: Using 'float' for money and 'short' for small counts.
 * 2. Global Variables: Declaring 'total' and 'count' outside functions so they retain their values.
 * 3. Integer vs Float Math: Why '100.0' is used instead of '100' (to avoid integer division).
 * 4. Function Return Types: Returning a 'float' from 'add_with_tax'.
 * 5. Running Totals: Using global variables inside a function to keep a cumulative sum.
 */

#include <stdio.h>

// GLOBAL VARIABLES
// These are declared outside any function, so they keep their values and can be accessed anywhere.
float total = 0.0;     // Total bill amount (float for decimals)
short count = 0;       // Number of items ordered (short is enough for small numbers)
short tax_percent = 6; // Sales tax rate (6%)

// FUNCTION DEFINITION
// Adds tax to a single item's price, updates the global total and count, then returns the new total.
float add_with_tax(float f)
{
    // Calculate tax rate. We use 100.0 (not 100) to force floating-point division.
    // If we used 100, 6 / 100 would equal 0 in C (integer division), losing the tax!
    float tax_rate = 1 + tax_percent / 100.0;
    
    // Update the global total by adding the item price plus tax
    total = total + (f * tax_rate);
    
    // Increment the global item count
    count = count + 1;
    
    // Return the new running total
    return total;
}

// MAIN FUNCTION
int main()
{
    // Local variable to store the price of the current item (float for decimals)
    float val;

    // Prompt the user for the first item
    printf("Price of item: ");

    // Loop as long as the user enters a valid float
    while (scanf("%f", &val) == 1) {
        
        // Call add_with_tax and print the running total with 2 decimal places
        printf("Total so far: %.2f\n", add_with_tax(val));
        
        // Prompt for the next item
        printf("Price of item: ");
    }

    // After the loop ends (user enters something invalid or hits Ctrl+D), print final results
    printf("\nFinal total: %.2f\n", total);
    printf("Number of items: %hi\n", count);
    
    return 0;
}
