/*
 * PURPOSE:
 * This program demonstrates dynamic memory allocation using malloc() and free().
 * It requests memory for a single integer, stores a value in it, prints it, 
 * and then releases the memory back to the system.
 *
 * WHAT IT TEACHES:
 * 1. malloc(): Asking the heap for memory at runtime.
 * 2. Pointers: Using the returned address to store and access data.
 * 3. free(): Returning the memory to prevent memory leaks.
 */

#include <stdio.h>
#include <stdlib.h> // REQUIRED for malloc() and free()

int main() {
    // 1. Request memory from the heap for one integer (usually 4 bytes)
    // malloc returns a void* pointer, so we cast it to int*
    int *p = (int*) malloc(sizeof(int));
    
    // 2. ALWAYS check if malloc succeeded. 
    // If the system is out of memory, malloc returns NULL.
    if (p == NULL) {
        printf("Memory allocation failed!\n");
        return 1; // Exit with an error code
    }

    // 3. Use the memory. The * operator dereferences the pointer to store the value 42.
    *p = 42;
    
    // 4. Print the value by dereferencing the pointer again.
    printf("Value: %i\n", *p);
    
    // 5. ALWAYS free the memory when you are done. 
    // This returns the "locker key" back to the operating system.
    free(p);
    
    // 6. (Good practice) Set the pointer to NULL after freeing.
    // This prevents "dangling pointers" (pointers pointing to deleted memory).
    p = NULL; 
    
    return 0;
}
