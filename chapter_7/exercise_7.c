/*
 * ============================================================================
 * PURPOSE:
 * This program calculates the total price of a drink order.
 * It uses a variadic function 'total()' that accepts a variable number of 
 * drink arguments and sums their prices using the 'price()' function.
 *
 * WHAT IT TEACHES:
 * 1. Real-world use of Variadic Functions (va_list, va_arg).
 * 2. How to pass Enums as variable arguments.
 * 3. How to build a cumulative sum using a loop and a helper function.
 * ============================================================================
 */

#include <stdio.h>
#include <stdarg.h> // Required for va_list, va_start, va_arg, va_end

// ============================================================================
// ENUM DEFINITION (The Drinks Menu)
// ============================================================================
// These are our cocktail types. C assigns them integer values starting from 0.
typedef enum {
    MONKEY_GLAND, // 0
    MUDLSIDE,     // 1
    FUZZY_NAVEL,  // 2
    ZOMBIE        // 3
} drink;

// ============================================================================
// HELPER FUNCTION: price
// ============================================================================
// Returns the price of a single drink based on its Enum value.
double price(drink d) {
    switch(d) {
        case MONKEY_GLAND: return 4.82;
        case MUDLSIDE:     return 6.79;
        case FUZZY_NAVEL:  return 5.31;
        case ZOMBIE:       return 5.89;
        default:           return 0.0;
    }
}

// ============================================================================
// VARIADIC FUNCTION: total
// ============================================================================
// Takes a fixed number of args (int args) and then a variable list of drinks (...)
double total(int args, ...) 
{
    // 1. Initialize the total sum to zero
    double total = 0.0;
    
    // 2. Declare the va_list to hold the variable arguments
    va_list ap;
    
    // 3. Start reading arguments. 'args' is the last fixed parameter.
    va_start(ap, args);
    
    int i;
    // 4. Loop exactly 'args' times (the number of drinks ordered)
    for (i = 0; i < args; i++) {
        
        // 5. Fetch the next argument. We cast it to type 'drink' (which is an int under the hood).
        drink d = va_arg(ap, drink);
        
        // 6. Add the price of this specific drink to the running total
        total = total + price(d);
    }
    
    // 7. Clean up the argument list
    va_end(ap);
    
    // 8. Return the final sum
    return total;
}

// ============================================================================
// MAIN FUNCTION
// ============================================================================
int main()
{
    // Call the total() function with different numbers of drinks.
    // The first argument is always the COUNT of drinks that follow.
    
    // 2 drinks: MONKEY_GLAND (4.82) + MUDLSIDE (6.79) = 11.61
    printf("Price is %.2f\n", total(2, MONKEY_GLAND, MUDLSIDE));
    
    // 3 drinks: MONKEY_GLAND (4.82) + MUDLSIDE (6.79) + FUZZY_NAVEL (5.31) = 16.92
    printf("Price is %.2f\n", total(3, MONKEY_GLAND, MUDLSIDE, FUZZY_NAVEL));
    
    // 1 drink: ZOMBIE (5.89)
    printf("Price is %.2f\n", total(1, ZOMBIE));
    
    return 0;
}
