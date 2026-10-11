//"This code demonstrates how to change the positions of characters inside an array using a temporary variable. In other words, it is the logic of 'shuffling cards'."

// Include the standard input/output library for puts
#include <stdio.h>

// The entry point of the program
int main() {

    // Declare a character array (string) and initialize it with "JQK"
    // This means: cards[0] = 'J', cards[1] = 'Q', cards[2] = 'K'
    char cards[] = "JQK";

    // Store the last card ('K') in a temporary variable called a_card
    // We do this because we will overwrite its position later
    char a_card = cards[2];

    // Move the middle card ('Q') to the last position
    // Now the array becomes: 'J', 'Q', 'Q' (temporarily)
    cards[2] = cards[1];

    // Move the first card ('J') to the middle position
    // Now the array becomes: 'J', 'J', 'Q' (temporarily)
    cards[1] = cards[0];

    // Put the saved last card ('K') into the first position
    // Now the array becomes: 'K', 'J', 'Q'
    cards[0] = a_card;

    // Print the final shuffled string to the screen
    puts(cards);

    // Return 0 to indicate successful program execution
    return 0;
}
