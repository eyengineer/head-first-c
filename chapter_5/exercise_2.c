/*
 * PURPOSE:
 * This program demonstrates deeply nested structs. It models a fish
 * with specific meal and exercise preferences, and prints a formatted label.
 *
 * WHAT IT TEACHES:
 * 1. Multi-level Nesting: A struct inside a struct inside a struct.
 * 2. Chained Dot Operators: Accessing data like a.care.food.weight.
 * 3. Formatted Output: Using %.2f for floats to show decimals properly.
 */

#include <stdio.h>

// Level 1: Inner Structs
struct exercise {
    const char *description;
    float duration;
};

struct meal {
    const char *ingredients;
    float weight;
};

// Level 2: Middle Struct (Contains Level 1)
struct preferences {
    struct meal food;
    struct exercise exercise;
};

// Level 3: Outer Struct (Contains Level 2)
struct fish {
    const char *name;
    const char *species;
    int teeth;
    int age;
    struct preferences care;
};

// Function to print the label
void label(struct fish a)
{
    printf("Name:%s\nSpecies:%s\n%i years old, %i teeth\n",
           a.name, a.species, a.age, a.teeth);
           
    // Notice the chained dots: a -> care -> food -> weight
    printf("Feed with %2.2f lbs of %s and allow to %s for %2.2f hours\n",
           a.care.food.weight, a.care.food.ingredients,
           a.care.exercise.description, a.care.exercise.duration);
}

int main()
{
    // Initializing the nested struct with nested braces
    struct fish snappy = {"Snappy", "Piranha", 69, 4, 
                          {{"meat", 0.2}, {"swim in the jacuzzi", 7.5}}};
    
    label(snappy);
    return 0;
}
