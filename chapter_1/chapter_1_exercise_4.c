// Standard input/output functions (printf, puts, scanf)
#include <stdio.h>
// For the atoi function (converts string to integer)
#include <stdlib.h> 


// Entry point of the program
int main() {

    // Array to hold the card name (max 2 chars + null terminator)
    char card_name[3];
    // Card counter variable, starts at 0
    int count = 0;
    
    // Loop continues until the user types 'X'

    while (card_name[0] != 'X') {
        // Ask the user for the card name
        puts("Enter the card_name: ");
        // Read at most 2 characters from the user into card_name
        scanf("%2s", card_name);
        // Variable to hold the card's numeric value, reset each iteration
        int val = 0;
        

        // Determine the card's value based on its first character
        switch (card_name[0]) {
            // K, Q, J cards have a value of 10
            case 'K':
            case 'Q':
            case 'J':
                val = 10;
                break;
            // A card has a value of 11
            case 'A':
                val = 11;
                break;
            // If 'X' is entered, go back to the loop condition to exit
            case 'X':
                continue;
            // All other cases (numbers or invalid inputs)
            default:
                // Convert the string to an integer (e.g., "5" -> 5)
               val = atoi(card_name);

                // If the value is less than 1 or greater than 10, it's invalid
                if ((val < 1) || (val > 10)) {
                    // Show an error message to the user
                    puts("I don't understand that value!");
                    // Skip the counter update and go back to the loop
                    continue;
                }
        }
        // If the card value is between 3 and 6, increment the counter
        if ((val > 2) && (val < 7)) {
            count++;
        // If the card value is 10, decrement the counter
        } else if (val == 10) {
            count--;
        }
        // Print the current count to the screen
        printf("Current count: %i\n", count);
    }
    // Exit the program successfully
    return 0;
}
