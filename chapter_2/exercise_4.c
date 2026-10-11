//A pointer doesn't copy data; it shares the address. If you change the data at that address, anyone pointing to it sees the change. 

// Include the standard input/output library for printf
#include <stdio.h>

// The entry point of the program
int main()
{
    // Declare a character array and initialize it with the string "Alive"
    // This creates a real array in memory (on the stack)
    char masked_raider[] = "Alive";

    // Declare a pointer to a character and point it to the masked_raider array
    // This pointer now holds the memory address of the first character of the array
    char *jimmy = masked_raider;

    // Print the current values. Both will show "Alive" because jimmy points to the same memory
    printf("Masked raider is %s, Jimmy is %s\n", masked_raider, jimmy);

    // Modify the array by changing individual characters
    // Note: We are changing the original array, not a copy
    masked_raider[0] = 'D'; // 'A' becomes 'D'
    masked_raider[1] = 'E'; // 'l' becomes 'E'
    masked_raider[2] = 'A'; // 'i' becomes 'A'
    masked_raider[3] = 'D'; // 'v' becomes 'D'
    masked_raider[4] = '!'; // 'e' becomes '!'

    // Print the values again. Both will now show "DEAD!" 
    // This is because jimmy points to the same memory that was just modified
    printf("Masked raider is %s, Jimmy is %s\n", masked_raider, jimmy);

    // Return 0 to indicate successful program execution
    return 0;
}
