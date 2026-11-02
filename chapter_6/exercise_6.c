/*
 * PURPOSE:
 * This program is the FIXED version of the previous exercise. 
 * It demonstrates the correct way to replace a dynamically allocated string.
 * Instead of just overwriting the pointer, we free the old memory first.
 *
 * WHAT IT TEACHES:
 * 1. How to prevent memory leaks by using free() before reassignment.
 * 2. The importance of tracking every malloc/strdup with a corresponding free.
 */

#include <stdio.h>
#include <stdlib.h> // Required for malloc() and free()
#include <string.h> // Required for strdup()

// ============================================================================
// STRUCT DEFINITION
// ============================================================================
// A simple Node structure for our linked list.
typedef struct node {
    char *question;      // Pointer to the dynamically allocated question string
    struct node *next;   // Pointer to the next node in the list
} node;

// ============================================================================
// FUNCTION: create
// ============================================================================
// This function allocates memory for a new node and copies the given string.
node* create(char *question)
{
    // 1. Allocate memory for the node structure itself on the Heap.
    node *n = malloc(sizeof(node));
    
    // 2. Allocate memory for the string and copy the text into it.
    // This creates a deep copy, so the node owns its own string.
    n->question = strdup(question);
    
    // 3. Initialize the next pointer to NULL (end of list).
    n->next = NULL;
    
    // 4. Return the address of the new node.
    return n;
}

// ============================================================================
// MAIN FUNCTION
// ============================================================================
int main()
{
    // 1. Create the first node.
    // The pointer 'start' points to the node.
    // 'start->question' points to a NEW string in the Heap ("Has a mustache?").
    node *start = create("Has a mustache?");
    
    // 2. Create the second node.
    // 'second' points to the new node.
    // 'second->question' points to a NEW string ("Loretta Barnsworth").
    node *second = create("Loretta Barnsworth");
    
    // 3. Link the first node to the second node.
    start->next = second;

    printf("Replacing the question...\n");
    
    // ========================================================================
    // THE FIX: FREE THE OLD MEMORY BEFORE OVERWRITING
    // ========================================================================
    // In the buggy version, we just did: start->question = strdup("...");
    // This lost the pointer to the old string, causing a leak.
    // 
    // Now, we FREE the old string first. 
    // This tells the system: "I don't need 'Has a mustache?' anymore."
    free(start->question); 
    
    // NOW, we allocate a new string and assign it to the same pointer.
    // The pointer now safely points to the new string on the Heap.
    start->question = strdup("Has a facial scar?"); 

    // ========================================================================
    // CLEANUP
    // ========================================================================
    // 4. Free the new string ("Has a facial scar?").
    free(start->question);
    
    // 5. Free the second node's string ("Loretta Barnsworth").
    free(second->question);
    
    // 6. Free the structs themselves (the "boxes").
    free(start);
    free(second);

    printf("Program finished. Did we leak memory?\n");
    return 0;
}
