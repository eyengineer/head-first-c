/*
 * PURPOSE:
 * This program manually creates a Linked List of islands and inserts a new island 
 * in the middle of the chain. It demonstrates how pointers act as "links" between structs.
 *
 * WHAT IT TEACHES:
 * 1. Recursive Structs: A struct that contains a pointer to its own type.
 * 2. Traversal: How to walk through a list using a pointer.
 * 3. Pointer Manipulation: How to redirect pointers to insert data without shifting arrays.
 */

#include <stdio.h>

// ============================================================================
// STRUCT DEFINITION
// ============================================================================
// This defines the "Node" of our linked list.
typedef struct island {
    char *name;          // Data: Name of the island
    char *opens;         // Data: Opening time
    char *closes;        // Data: Closing time
    struct island *next; // Link: A pointer to the NEXT island in the chain. 
                         // It holds a memory ADDRESS, not the actual struct.
} island;

// ============================================================================
// DISPLAY FUNCTION (Traversal)
// ============================================================================
void display(island *start)
{
    // We create a temporary pointer 'i' that points to the first island.
    // Why? Because if we move 'start' itself, we will lose the beginning of our list!
    island *i = start; 
    
    // The for loop has 3 parts:
    // 1. Initialization: (Empty here, because we already did 'island *i = start;')
    // 2. Condition: 'i != NULL' -> Keep looping as long as 'i' is pointing to a real island.
    // 3. Increment: 'i = i->next' -> After printing, move 'i' to the next island in the chain.
    for (; i != NULL; i = i->next) {
        
        // i->name is the same as (*i).name. It means "Go to the address 'i', find the 'name' field".
        printf("Name: %s open: %s-%s\n", i->name, i->opens, i->closes);
    }
}

// ============================================================================
// MAIN FUNCTION
// ============================================================================
int main()
{
    // ========================================================================
    // STEP 1: Create the Islands (Nodes)
    // ========================================================================
    // We create 4 separate variables. Each one is a struct on the Stack.
    // Notice that 'next' is set to NULL. This means they are currently NOT connected to anything.
    island amity = {"Amity", "09:00", "17:00", NULL};
    island craggy = {"Craggy", "09:00", "17:00", NULL};
    island isla_nublar = {"Isla Nublar", "09:00", "17:00", NULL};
    island shutter = {"Shutter", "09:00", "17:00", NULL};

    // ========================================================================
    // STEP 2: Link them together
    // ========================================================================
    // We use the '&' (address-of) operator to get the memory address of the next island.
    // amity.next now holds the address of craggy.
    amity.next = &craggy;
    
    // craggy.next holds the address of isla_nublar.
    craggy.next = &isla_nublar;
    
    // isla_nublar.next holds the address of shutter.
    isla_nublar.next = &shutter;
    
    // Now the chain is: Amity -> Craggy -> Isla Nublar -> Shutter -> NULL

    // ========================================================================
    // STEP 3: Insert Skull Island in the middle
    // ========================================================================
    // Let's insert "Skull" between "Isla Nublar" and "Shutter".
    // First, create the new island. Its 'next' is NULL for now.
    island skull = {"Skull", "09:00", "17:00", NULL};

    // 1. Point Skull's 'next' to whatever Isla Nublar is currently pointing to (Shutter).
    // skull.next now holds the address of shutter.
    skull.next = isla_nublar.next; 
    
    // 2. Point Isla Nublar's 'next' to the new Skull island.
    // isla_nublar.next now holds the address of skull.
    isla_nublar.next = &skull;

    // New chain: Amity -> Craggy -> Isla Nublar -> Skull -> Shutter -> NULL
    // Notice how we ONLY changed two pointers. If this were an array, we would have 
    // to shift all elements after Isla Nublar to make room! This is the power of linked lists.

    // ========================================================================
    // STEP 4: Display the list
    // ========================================================================
    // We pass the address of the FIRST island (amity) to start the tour.
    display(&amity);

    return 0;
}
