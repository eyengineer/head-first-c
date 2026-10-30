/*
 * PURPOSE:
 * This program reads GPS coordinates (latitude and longitude) and info from input.
 * It validates the data to ensure coordinates are within realistic bounds.
 * If valid, it formats the output as a JSON array. If invalid, it prints an error 
 * message to Standard Error (stderr) and exits with an error code.
 *
 * WHAT IT TEACHES:
 * 1. Data Validation: Checking if input numbers are within real-world limits.
 * 2. Logical OR (||): Using OR to check if a value is outside a specific range.
 * 3. Standard Error (stderr): Separating error messages from normal data output.
 * 4. fprintf(): Printing formatted messages to a specific stream (like stderr).
 * 5. Return Status: Returning a non-zero code (2) to indicate a specific error.
 * 6. scanf Return Value: Understanding how scanf returns the number of items read.
 */

#include <stdio.h>

int main()
{
    // Variables to store the parsed data
    float latitude;
    float longitude;
    char info[80];
    int started = 0; // Flag to track if we are at the first element (for JSON commas)

    // Start the JSON array format
    puts("data=[");

    // scanf attempts to read a float, a comma, a float, a comma, and a string (info).
    // It returns the number of successfully matched and assigned input items.
    // Here, it expects to successfully read 3 items: latitude, longitude, and info.
    // The loop continues as long as exactly 3 items are read successfully.
    while (scanf("%f,%f,%79[^\n]", &latitude, &longitude, info) == 3) {
        
        // If this is not the first element, print a comma and newline to separate JSON objects
        if (started)
            printf(",\n");
        else
            started = 1; // Mark that the first element has been processed

        // Validate the latitude: it must be between -90.0 and 90.0
        if ((latitude < -90.0) || (latitude > 90.0)) {
            // Use fprintf to print the error to the standard error stream (stderr)
            // This ensures error messages don't get mixed with normal data output (stdout)
            fprintf(stderr, "Invalid latitude: %f\n", latitude);
            return 2; // Exit the program immediately with an error status code 2
        }

        // Validate the longitude: it must be between -180.0 and 180.0
        if ((longitude < -180.0) || (longitude > 180.0)) {
            // Print the longitude error to standard error
            fprintf(stderr, "Invalid longitude: %f\n", longitude);
            return 2; // Exit the program with an error status code 2
        }

        // If both coordinates are valid, print the formatted JSON object to standard output (stdout)
        printf("{latitude: %f, longitude: %f, info: '%s'}", latitude, longitude, info);
    }

    // Close the JSON array format
    puts("\n]");
    
    return 0; // Exit the program successfully
}
