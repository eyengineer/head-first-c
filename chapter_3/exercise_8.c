/*
 * PURPOSE:
 * This program is an order-taking tool for a pizza restaurant.
 * It demonstrates how to parse command-line options using getopt().
 * Users can specify options like -t (thick crust) and -d (delivery address),
 * followed by a list of ingredients.
 *
 * WHAT IT TEACHES:
 * 1. getopt(): Parsing command-line options.
 * 2. optarg & optind: Accessing option arguments and skipping processed options.
 * 3. switch statement for options: Handling different flags (e.g., 't' and 'd').
 */

#include <stdio.h>
#include <unistd.h> // Required for getopt()

int main(int argc, char *argv[])
{
    // Default delivery address is empty
    char *delivery = "";
    // Flag for thick crust (0 = false, 1 = true)
    int thick = 0;
    // Counter for looping through ingredients
    int count = 0;
    // Variable to hold the current option character
    char ch;

    // The string "d:t" tells getopt:
    // 'd' is a valid option that REQUIRES an argument (because of the colon)
    // 't' is a valid option that takes NO argument
    while ((ch = getopt(argc, argv, "d:t")) != EOF) {
        switch (ch) {
            case 'd':
                // If -d is found, optarg points to the next word (the address)
                delivery = optarg;
                break;
            case 't':
                // If -t is found, set thick to 1 (true)
                thick = 1;
                break;
            default:
                // If an unknown option is passed, print error and exit
                fprintf(stderr, "Unknown option: '%s'\n", optarg);
                return 1;
        }
    }

    // Adjust argc and argv to skip past the processed options
    // Now argv[0] points to the first actual ingredient
    argc -= optind;
    argv += optind;

    // If the -t option was used, print it
    if (thick)
        puts("Thick crust.");

    // If a delivery address was provided, print it
    // delivery[0] checks if the string is not empty
    if (delivery[0])
        printf("To be delivered %s.\n", delivery);

    // Print the ingredients
    puts("Ingredients:");
    for (count = 0; count < argc; count++)
        puts(argv[count]);

    return 0;
}
