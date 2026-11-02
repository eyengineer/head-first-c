/*
 * PURPOSE:
 * This program demonstrates how to use 'enum' and 'union' together with structs.
 * It models a fruit order where the quantity can be a count (integer), 
 * a weight (float), or a volume (float).
 *
 * WHAT IT TEACHES:
 * 1. enum: Creating custom names for integer constants (COUNT, POUNDS, PINTS).
 * 2. union: Storing different data types in the same memory location.
 * 3. Designated Initializers: Initializing specific struct fields by name (.amount.count = 144).
 * 4. Tracking Types: Using an enum variable inside a struct to remember which union field is currently active.
 */

#include <stdio.h>

// ============================================================================
// 1. ENUM: Defining the types of measurement
// ============================================================================
// This creates three constants: COUNT=0, POUNDS=1, PINTS=2.
// We use this to track WHICH type of quantity we are storing in the union.
typedef enum {
    COUNT, POUNDS, PINTS
} unit_of_measure;

// ============================================================================
// 2. UNION: Storing the quantity
// ============================================================================
// A union only allocates enough memory for its largest field (in this case, float).
// All three fields share the same memory address. Only ONE can be used at a time.
typedef union {
    short count;    // Used if the order is by count (e.g., 144 apples)
    float weight;   // Used if the order is by weight (e.g., 17.6 lbs)
    float volume;   // Used if the order is by volume (e.g., 10.5 pints)
} quantity;

// ============================================================================
// 3. STRUCT: Combining everything
// ============================================================================
typedef struct {
    const char *name;       // Name of the fruit
    const char *country;    // Country of origin
    quantity amount;        // The actual quantity (union)
    unit_of_measure units;  // The flag telling us what kind of quantity it is (enum)
} fruit_order;

// ============================================================================
// FUNCTION: Display the order
// ============================================================================
void display(fruit_order order)
{
    printf("This order contains ");
    
    // We check the 'units' enum to know which field of the 'amount' union to print.
    // If we didn't check, we might read a float as a short and get garbage data.
    if (order.units == PINTS)
        printf("%2.2f pints of %s\n", order.amount.volume, order.name);
    else if (order.units == POUNDS)
        printf("%2.2f lbs of %s\n", order.amount.weight, order.name);
    else // It must be COUNT
        printf("%i %s\n", order.amount.count, order.name);
}

// ============================================================================
// MAIN FUNCTION
// ============================================================================
int main()
{
    // Using designated initializers (.amount.count=144) to set specific fields.
    // Notice that for 'apples', we set .amount.count and the unit is COUNT.
    fruit_order apples = {"apples", "England", .amount.count=144, COUNT};
    
    // For strawberries, we set .amount.weight and the unit is POUNDS.
    fruit_order strawberries = {"strawberries", "Spain", .amount.weight=17.6, POUNDS};
    
    // For orange juice, we set .amount.volume and the unit is PINTS.
    fruit_order oj = {"orange juice", "U.S.A.", .amount.volume=10.5, PINTS};
    
    // Call the function to display each order
    display(apples);
    display(strawberries);
    display(oj);
    
    return 0;
}
