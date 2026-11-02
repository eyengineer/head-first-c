/*
 * PURPOSE:
 * This program fixes the "Vanishing Island" bug. 
 * It uses strdup() to create a deep copy of the string, so each island 
 * keeps its own name even if the original buffer changes.
 *
 * WHAT IT TEACHES:
 * 1. String Pointers: Why assigning pointers doesn't copy data.
 * 2. strdup(): How to safely copy strings to the Heap.
 * 3. Memory Leak Awareness: Why we must free() the strdup'd memory later.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h> // REQUIRED for strdup() and strlen()

// Define the structure for an island (Node of the linked list)
typedef struct island {
    char *name;          // Pointer to the island's name (will be stored on the Heap)
    char *opens;         // Pointer to opening time (points to read-only string literal)
    char *closes;        // Pointer to closing time (points to read-only string literal)
    struct island *next; // Pointer to the next island in the chain
} island;

// ============================================================================
// FUNCTION: create
// ============================================================================
// Takes a string pointer 'name' as input and creates a new island on the Heap.
island* create(char *name)
{
    // 1. Allocate memory for ONE island struct on the Heap.
    // sizeof(island) tells us exactly how many bytes are needed.
    island *i = malloc(sizeof(island));
    
    // 2. THE FIX: Use strdup to make a DEEP COPY of the name.
    // strdup() internally calls malloc to allocate space for the string and copies it.
    // Without this, 'i->name' would just point to the local 'name' array in main, 
    // which gets overwritten on the next fgets() call.
    i->name = strdup(name); 
    
    // 3. Assign string literals to opens and closes.
    // We DON'T need strdup here because string literals are stored in the read-only 
    // data section of memory, and their values never change.
    i->opens = "09:00";
    i->closes = "17:00";
    
    // 4. Initialize the next pointer to NULL to indicate the end of the list (for now).
    i->next = NULL;
    
    // 5. Return the address of the newly created island.
    return i;
}

// ============================================================================
// FUNCTION: display
// ============================================================================
// Traverses the linked list and prints each island's details.
void display(island *start)
{
    // Create a temporary pointer 'i' to walk the list without losing the 'start' pointer.
    island *i = start;
    
    // Loop until we reach the end of the list (NULL).
    // 'i = i->next' moves the pointer to the next island after each iteration.
    for (; i != NULL; i = i->next) {
        // Use the -> operator to access struct members via a pointer.
        // Print the name, opening time, and closing time.
        printf("Name: %s open: %s-%s\n", i->name, i->opens, i->closes);
    }
}

// ============================================================================
// FUNCTION: release
// ============================================================================
// Frees ALL dynamically allocated memory to prevent memory leaks.
// This is crucial because we used malloc() and strdup().
void release(island *start)
{
    island *i = start;
    island *next = NULL;
    
    // Loop through the list, freeing each node.
    for (; i != NULL; i = next) {
        // 1. Save the next pointer BEFORE freeing 'i'.
        // If we free 'i' first, we lose access to 'i->next' and the loop breaks.
        next = i->next; 
        
        // 2. Free the string that was allocated by strdup().
        // We must free the inner data first.
        free(i->name);  
        
        // 3. Free the struct itself that was allocated by malloc().
        free(i);        
    }
}

// ============================================================================
// MAIN FUNCTION
// ============================================================================
int main()
{
    // Declare a local character array (on the Stack) to temporarily hold the input.
    char name[80];
    
    // Read the first island name from the user.
    printf("Enter island name: ");
    fgets(name, 80, stdin);
    
    // Call create() to make a new island on the Heap. 
    // The 'name' array is passed by address, but create() makes a copy using strdup.
    island *p_island0 = create(name);
    
    // Read the second island name INTO THE SAME BUFFER.
    // If create() didn't use strdup, the first island would now be renamed!
    printf("Enter island name: ");
    fgets(name, 80, stdin);
    island *p_island1 = create(name);
    
    // Connect the first island to the second island.
    p_island0->next = p_island1;
    
    // Display the list starting from the first island.
    display(p_island0);
    
    // CLEAN UP: Release all memory allocated on the Heap.
    release(p_island0);
    
    return 0;
}
