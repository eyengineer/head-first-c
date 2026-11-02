/*
 * PURPOSE:
 * This program demonstrates deeply nested structs (a struct inside a struct inside a struct). 
 * It models a fish with specific meal and exercise preferences, and prints a formatted label.
 *
 * WHAT IT TEACHES:
 * 1. Multi-level Nesting: How to build complex data types by combining simpler ones.
 * 2. Chained Dot Operators: Accessing deeply nested data using paths like a.care.food.weight.
 * 3. Struct Initialization: Using nested curly braces {{ }} to assign values to nested structs.
 * 4. Formatted Output: Using %.2f to print floats with exactly two decimal places.
 */

#include <stdio.h>

// ============================================================================
// LEVEL 1: INNERMOST STRUCTS (The building blocks)
// ============================================================================

// Defines a template for an exercise routine
struct exercise {
    const char *description; // A string describing the exercise (e.g., "swim")
    float duration;          // How long the exercise lasts in hours
};

// Defines a template for a meal
struct meal {
    const char *ingredients; // A string describing the food (e.g., "meat")
    float weight;            // The weight of the food in pounds (lbs)
};

// ============================================================================
// LEVEL 2: MIDDLE STRUCT (Combining Level 1)
// ============================================================================

// Defines a template for a fish's preferences
struct preferences {
    struct meal food;        // Contains a 'meal' struct (defined above)
    struct exercise exercise;// Contains an 'exercise' struct (defined above)
};

// ============================================================================
// LEVEL 3: OUTERMOST STRUCT (Combining Level 2)
// ============================================================================

// Defines the main template for a fish
struct fish {
    const char *name;        // Fish's name
    const char *species;     // Fish's species
    int teeth;               // Number of teeth
    int age;                 // Age in years
    struct preferences care; // Contains a 'preferences' struct, named 'care'
};

// ============================================================================
// FUNCTION DEFINITION
// ============================================================================

// Takes a 'struct fish' as an argument (passed by value, meaning a copy is made)
void label(struct fish a)
{
    // Prints basic info. Accesses the direct members using the dot (.) operator.
    // \n means newline. %s is for strings, %i is for integers.
    printf("Name:%s\nSpecies:%s\n%i years old, %i teeth\n",
           a.name, a.species, a.age, a.teeth);
           
    // Prints the nested info. 
    // To get the weight: go to 'a', then 'care', then 'food', then 'weight'.
    // %2.2f means: print a float with a minimum width of 2 and exactly 2 decimal places.
    // Note the order of arguments must match the order of format specifiers in the string.
    printf("Feed with %2.2f lbs of %s and allow to %s for %2.2f hours\n",
           a.care.food.weight,         // Matches first %2.2f
           a.care.food.ingredients,    // Matches first %s
           a.care.exercise.description,// Matches second %s
           a.care.exercise.duration);  // Matches second %2.2f
}

// ============================================================================
// MAIN FUNCTION (Entry Point)
// ============================================================================
int main()
{
    // Declare a variable 'snappy' of type 'struct fish' and initialize it.
    // The initialization uses nested curly braces to match the nested structs.
    struct fish snappy = {
        "Snappy",                   // 1. name
        "Piranha",                  // 2. species
        69,                         // 3. teeth
        4,                          // 4. age
        {                           // 5. care (This is the 'struct preferences')
            {"meat", 0.2},          //   5a. food (This is the 'struct meal')
            {"swim in the jacuzzi", 7.5} // 5b. exercise (This is the 'struct exercise')
        }
    };
    
    // Call the label function, passing the 'snappy' struct as an argument
    label(snappy);
    
    // Return 0 to indicate successful execution
    return 0;
}
