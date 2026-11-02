/*
 * PURPOSE:
 * This program demonstrates how to use 'typedef' to create aliases (short names) 
 * for structs. It models a scuba diver with equipment details and prints a badge.
 *
 * WHAT IT TEACHES:
 * 1. typedef: Creating a new name for an existing data type.
 * 2. Removing the 'struct' keyword: After using typedef, you don't need to type 'struct' every time.
 * 3. Nested Structs with typedef: Using an aliased struct inside another aliased struct.
 */

#include <stdio.h>

// ============================================================================
// INNER STRUCT: Equipment
// ============================================================================
// We use 'typedef' to create an alias. 
// Instead of writing "struct equipment" every time, we can now just write "equipment".
typedef struct {
    float tank_capacity;    // Tank capacity in liters
    int tank_psi;           // Tank pressure in PSI (Pounds per Square Inch)
    const char *suit_material; // Material of the diving suit
} equipment; // 'equipment' is the new alias (type name)

// ============================================================================
// OUTER STRUCT: Diver
// ============================================================================
// We can give this struct a name ('scuba') AND an alias ('diver').
// The name 'scuba' is optional here, but the alias 'diver' is what we will use.
typedef struct scuba {
    const char *name;       // Diver's name
    equipment kit;          // Notice we use the alias 'equipment' here, not 'struct equipment'
} diver; // 'diver' is the new alias

// ============================================================================
// FUNCTION: Badge
// ============================================================================
// The parameter 'd' uses the alias 'diver' (not "struct scuba d").
void badge(diver d)
{
    // Accessing nested data. 
    // d.kit gives us the 'equipment' struct, then we access its members with .tank_capacity etc.
    printf("Name: %s Tank: %2.2f(%i) Suit: %s\n",
           d.name, d.kit.tank_capacity, d.kit.tank_psi, d.kit.suit_material);
}

// ============================================================================
// MAIN FUNCTION
// ============================================================================
int main()
{
    // Declare 'randy' as a 'diver'. 
    // Notice we don't write "struct scuba randy". We just write "diver randy".
    // Initialization: Nested braces are used for the nested 'equipment' struct.
    diver randy = {"Randy", {5.5, 3500, "Neoprene"}};
    
    // Call the badge function
    badge(randy);
    
    return 0;
}
