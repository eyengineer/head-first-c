/*
 * PURPOSE:
 * This program demonstrates how to pass a 'struct' to a function.
 * It creates a struct for a fish, and passes it to two functions 
 * (catalog and label) to print its details.
 *
 * WHAT IT TEACHES:
 * 1. Passing structs by value: The function receives a copy of the struct.
 * 2. Dot operator (.): Accessing struct members inside a function.
 */

#include <stdio.h>

// Define the struct template
struct fish {
    const char *name;
    const char *species;
    int teeth;
    int age;
};

// Function to print a catalog entry
void catalog(struct fish f)
{
    printf("%s is a %s with %i teeth. He is %i\n",
           f.name, f.species, f.teeth, f.age);
}

// Function to print a label
void label(struct fish f)
{
    printf("Name:%s\nSpecies:%s\n%i years old, %i teeth\n",
           f.name, f.species, f.age, f.teeth);
}

int main()
{
    // Create a struct variable 'snappy' and initialize it
    struct fish snappy = {"Snappy", "Piranha", 69, 4};
    
    // Pass the struct to the functions
    catalog(snappy);
    label(snappy);
    
    return 0;
}
