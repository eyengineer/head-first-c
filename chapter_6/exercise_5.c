/*
 * PURPOSE:
 * This program is a simulation to demonstrate a "Memory Leak". 
 * It mimics the SPIES expert system from the book, where a pointer is overwritten 
 * without freeing the old memory first. 
 *
 * WHAT IT TEACHES:
 * 1. How memory leaks happen (overwriting pointers).
 * 2. How to compile with debug info (-g).
 * 3. How to use valgrind to detect the exact line where the leak occurred.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ============================================================================
// STRUCT DEFINITION
// ============================================================================
// A simple node to hold a string (question) and a link to the next node.
typedef struct node {
    char *question;      // Pointer to a dynamically allocated string
    struct node *next;   // Pointer to the next node in the list
} node;

// ============================================================================
// FUNCTION: create
// ============================================================================
// Allocates memory for a new node and duplicates the given string.
node* create(char *question)
{
    // 1. Allocate memory on the Heap for the struct itself.
    node *n = malloc(sizeof(node));
    
    // 2. Allocate memory on the Heap for the string and copy the text into it.
    // strdup() is used to make a deep copy, so the node owns its own string.
    n->question = strdup(question);
    
    // 3. Initialize the next pointer to NULL.
    n->next = NULL;
    
    // 4. Return the pointer to the newly created node.
    return n;
}

// ============================================================================
// MAIN FUNCTION
// ============================================================================
int main()
{
    // 1. Create the first node. 
    // 'start' points to the node. 
    // The node's 'question' points to a NEW string on the Heap ("Has a mustache?").
    node *start = create("Has a mustache?");
    
    // 2. Create the second node.
    // 'second' points to the new node.
    // Its 'question' points to a NEW string on the Heap ("Loretta Barnsworth").
    node *second = create("Loretta Barnsworth");
    
    // 3. Link the first node to the second node.
    start->next = second;

    printf("Replacing the question...\n");
    
    // ========================================================================
    // THE MEMORY LEAK HAPPENS HERE!
    // ========================================================================
    // We are assigning a NEW string to 'start->question'.
    // BUT, we didn't free the OLD string ("Has a mustache?") first!
    // The pointer 'start->question' now points to the new string ("Has a facial scar?").
    // The old string is still sitting in the Heap, but we have lost the pointer to it.
    // We can NEVER free it now. This is a "Memory Leak".
    
    start->question = strdup("Has a facial scar?"); 

    // ========================================================================
    // CLEANUP
    // ========================================================================
    // 4. We free the NEW string ("Has a facial scar?").
    free(start->question);
    
    // 5. We free the second node's string ("Loretta Barnsworth").
    free(second->question);
    
    // 6. We free the structs themselves.
    free(start);
    free(second);

    // 7. End the program.
    // Even though we freed everything we had pointers to, the OLD string 
    // ("Has a mustache?") is still in the Heap. Valgrind will catch this!
    printf("Program finished. Did we leak memory?\n");
    return 0;
}
