/*
 * PURPOSE:
 * This code reads comma-separated data from the command line and formats it
 * into JSON format. It demonstrates how to parse multiple inputs with scanf 
 * and how to handle formatting (like commas) using a boolean flag.
 *
 * WHAT IT TEACHES:
 * 1. scanf with multiple formats: Reading float, float, and string at the same time.
 * 2. Pointers in scanf: Why we use '&' for numbers and not for arrays (strings).
 * 3. Boolean flags: Using an integer (started) to track the first iteration.
 * 4. JSON formatting: Converting plain text input into structured data.
 */

#include <stdio.h>

int main()
{
    // Declare variables to hold the parsed data
    float latitude;
    float longitude;
    char info[80];
    
    // Use an integer as a boolean flag to track if the first item has been read
    // 0 means false, 1 means true
    int started = 0;

    // Start the JSON array
    puts("data=[");

    // Read three inputs at a time: two floats and a string until the end of file
    // %f expects a float pointer (&latitude), %79[^\n] expects a char array (info)
    while (scanf("%f,%f,%79[^\n]", &latitude, &longitude, info) == 3) {

        // If we have already printed at least one line, print a comma and newline
        // to separate the JSON objects
        if (started)
            printf(",\n");
        else
            // Once the loop starts, set 'started' to 1 (true) so the next iteration prints a comma
            started = 1;

        // Print the data in JSON format
        // No '&' is needed here because printf wants the VALUES, not the addresses
        printf("{latitude: %f, longitude: %f, info: '%s'}", latitude, longitude, info);
    }

    // Close the JSON array
    puts("\n]");
    
    return 0;
}
