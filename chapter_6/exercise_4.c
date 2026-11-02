/*
 * PURPOSE:
 * This program reads a list of island names from a file (or Standard Input), 
 * creates a dynamically allocated linked list of these islands, 
 * displays them, and finally releases all allocated memory.
 *
 * WHAT IT TEACHES:
 * 1. Creating a linked list dynamically from user input/file.
 * 2. Using strdup() to copy strings safely.
 * 3. Properly freeing memory (in the correct order) to avoid leaks.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct island {
    char *name;
    char *opens;
    char *closes;
    struct island *next;
} island;

// Function to create a new island (allocates memory and copies the name)
island* create(char *name)
{
    island *i = malloc(sizeof(island));
    i->name = strdup(name); // Deep copy of the name
    i->opens = "09:00";
    i->closes = "17:00";
    i->next = NULL;
    return i;
}

// Function to display the linked list
void display(island *start)
{
    island *i = start;
    for (; i != NULL; i = i->next) {
        printf("Name: %s\nOpen: %s-%s\n", i->name, i->opens, i->closes);
    }
}

// Function to release memory (CRITICAL: free name first, then the struct)
void release(island *start)
{
    island *i = start;
    island *next = NULL;
    for (; i != NULL; i = next) {
        next = i->next; // Save next before freeing current
        free(i->name);  // Free the strdup'd string
        free(i);        // Free the struct itself
    }
}

int main()
{
    // Pointers to track the start and current end of the list
    island *start = NULL;
    island *i = NULL;
    island *next = NULL;
    char name[80];

    // Read strings from standard input until EOF (Ctrl+D)
    // The for loop does the reading and assignment in one line
    for (; fgets(name, 80, stdin) != NULL; i = next) {
        
        // Remove the newline character from fgets
        name[strcspn(name, "\n")] = 0;
        
        // Create a new island
        next = create(name);

        // If the list is empty, set 'start' to the first island
        if (start == NULL)
            start = next;

        // If this is not the first island, link the previous island to this one
        if (i != NULL)
            i->next = next;
    }

    // Display the list
    display(start);

    // Free all memory
    release(start);

    return 0;
}
