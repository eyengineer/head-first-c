/*
 * ============================================================================
 * PURPOSE:
 * This program demonstrates how to use an array of function pointers 
 * to replace a long switch/case statement. This makes the code cleaner, 
 * more scalable, and easier to maintain.
 *
 * WHAT IT TEACHES:
 * 1. Array of Function Pointers: Storing function addresses in an array.
 * 2. Using Enums as Indices: Enums (0, 1, 2...) can be used to look up the correct function.
 * 3. Dynamic Function Calls: Calling the right function based on data at runtime.
 * ============================================================================
 */

#include <stdio.h> // Required for printf() and puts()

// ============================================================================
// ENUM DEFINITION
// ============================================================================
// An enum (enumeration) is a way to give names to integer constants.
// By default, C assigns values starting from 0: DUMP = 0, SECOND_CHANCE = 1, MARRIAGE = 2.
// We use this to safely index into our array of function pointers later.
typedef enum {
    DUMP,           // 0
    SECOND_CHANCE,  // 1
    MARRIAGE        // 2
} response_type;

// ============================================================================
// STRUCT DEFINITION
// ============================================================================
// A struct groups different data types together.
// Here, we group a string (name) and an enum (type) to represent a person's response.
typedef struct {
    const char *name;   // A pointer to a read-only string (the person's name)
    response_type type; // The enum value (DUMP, SECOND_CHANCE, or MARRIAGE)
} response;

// ============================================================================
// HANDLER FUNCTIONS
// ============================================================================
// These are the functions that will be stored in our array.
// All of them MUST have the exact same signature: take a 'response' and return 'void'.

void dump(response r) {
    // %s is a format specifier for a string.
    // \n is the newline character (moves to the next line).
    // r.name accesses the 'name' field of the 'r' struct.
    printf("Dear %s,\n", r.name);
    
    // puts() prints a string and automatically adds a newline (\n) at the end.
    puts("Unfortunately your last date contacted us to say that they will not be seeing you again");
}

void second_chance(response r) {
    printf("Dear %s,\n", r.name);
    puts("Good news: your last date has asked us to arrange another meeting. Please call ASAP.");
}

void marriage(response r) {
    printf("Dear %s,\n", r.name);
    puts("Congratulations! Your last date has contacted us with a proposal of marriage.");
}

// ============================================================================
// ARRAY OF FUNCTION POINTERS (THE MAGIC TRICK)
// ============================================================================
// Syntax breakdown: void (*replies[])(response)
// - 'void': The functions in this array return nothing.
// - '(*replies[])': This is an array of pointers. 
// - '(response)': The functions take a 'response' struct as a parameter.
// The array is initialized with the names of the functions (which act as memory addresses).
// The order is crucial: index 0 = dump, index 1 = second_chance, index 2 = marriage.
void (*replies[])(response) = {dump, second_chance, marriage};

// ============================================================================
// MAIN FUNCTION
// ============================================================================
int main() {
    // Create an array of 'response' structs and initialize them.
    // The compiler automatically fills the structs with the provided data.
    response r[] = {
        {"Mike", DUMP}, 
        {"Luis", SECOND_CHANCE},
        {"Matt", SECOND_CHANCE}, 
        {"William", MARRIAGE}
    };
    
    int i; // Loop counter
    // Loop through each element in the 'r' array (4 elements).
    for (i = 0; i < 4; i++) {
        
        // DETAILED BREAKDOWN OF THIS LINE:
        // 1. r[i].type: Access the 'type' field of the i-th response.
        //    This returns an enum value (0, 1, or 2).
        // 2. replies[...]: Use that enum value as an index into the array of function pointers.
        //    If type is DUMP (0), it selects 'replies[0]' (which is the 'dump' function).
        // 3. (r[i]): Call the selected function and pass the entire 'r[i]' struct to it.
        (replies[r[i].type])(r[i]); 
    }
    
    return 0; // Indicate successful execution
}
