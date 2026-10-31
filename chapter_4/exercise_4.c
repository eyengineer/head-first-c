/*
 * ============================================================================
 * PURPOSE:
 * This program calculates a restaurant bill, including tax. It reads prices
 * from the user in a loop, adds the tax, and keeps a running total.
 * The specific goal of this file is to demonstrate FUNCTION PROTOTYPES and
 * why the order of function definitions matters in C.
 *
 * WHAT IT TEACHES:
 * 1. Function Prototypes: Informing the compiler about a function's existence
 *    before its actual definition (usually placed at the top of the file).
 * 2. Global Variables: Variables declared outside main() that can be accessed
 *    and modified by ANY function in the file.
 * 3. Scope: Understanding that 'total' and 'count' live for the whole program.
 * 4. Float Arithmetic: Using 100.0 to prevent integer division truncation.
 * ============================================================================
 */

#include <stdio.h>

// ============================================================================
// GLOBAL VARIABLES
// ============================================================================
// These variables are declared OUTSIDE of any function. This means they are 
// stored in the "Global" memory segment and can be read/written by any function.
// They persist as long as the program is running.

float total = 0.0;     // Holds the accumulating total price.
short count = 0;       // Holds how many items have been scanned. (short is efficient).
short tax_percent = 6; // Holds the tax percentage. We can change this easily later.

// ============================================================================
// FUNCTION PROTOTYPE (The "Promise")
// ============================================================================
// C reads code from top to bottom. When the compiler reaches main() and sees 
// 'add_with_tax(val)', it needs to know what 'add_with_tax' is. 
// By putting this prototype here, we make a promise to the compiler: 
// "Hey, there is a function called add_with_tax that takes a float and returns a float.
// I will define its actual code at the bottom of the file. Trust me."
float add_with_tax(float f);

// ============================================================================
// MAIN FUNCTION
// ============================================================================
int main()
{
    // Local variable: Exists ONLY inside main(). Destroys when main() ends.
    float val; 

    // Prompt the user for the first item
    printf("Price of item: ");

    // Loop: Continues as long as the user enters a valid float number.
    // scanf returns 1 if it successfully reads a float, 0 or EOF if it fails.
    while (scanf("%f", &val) == 1) {
        
        // Call the function, pass the price (val), and print the result.
        // %.2f limits the output to 2 decimal places (like real currency).
        // Because we have the prototype above, the compiler knows this works.
        printf("Total so far: %.2f\n", add_with_tax(val));
        
        // Ask for the next item
        printf("Price of item: ");
    }
    
    // When the loop ends (user hits Ctrl+D), print the final results.
    // It uses the GLOBAL variables 'total' and 'count' that were updated inside 
    // the add_with_tax function!
    printf("\nFinal total: %.2f\n", total);
    
    // %hi is the format specifier for a 'short' integer.
    printf("Number of items: %hi\n", count);
    
    return 0;
}

// ============================================================================
// FUNCTION DEFINITION (The Actual Work)
// ============================================================================
// This is where the compiler finally sees what add_with_tax actually does.
// It takes a float 'f' (the price of one item) as input.
float add_with_tax(float f)
{
    // Calculate the tax multiplier. 
    // CRITICAL: We use 100.0, not 100. If we used 100 (integer), 6/100 would 
    // evaluate to 0 because integers can't hold decimals. Adding .0 forces float math.
    float tax_rate = 1 + tax_percent / 100.0;
    
    // Update the GLOBAL total variable. 
    // We multiply the item price (f) by the tax rate, and add it to the existing total.
    total = total + (f * tax_rate);
    
    // Increment the GLOBAL count variable by 1.
    count = count + 1;
    
    // Return the new total back to main() so it can be printed.
    return total;
}
