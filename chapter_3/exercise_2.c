
/*
 * PURPOSE:
 * This program reads GPS coordinates (latitude and longitude) from standard input,
 * formats them into JSON, and adds a crucial layer of data validation.
 * If the coordinates are outside the valid geographic ranges, it aborts the program.
 *
 * WHAT IT TEACHES:
 * 1. Data Validation: Checking if input data makes sense in the real world.
 * 2. Logical OR (||): Using the OR operator to check if a value falls outside a range.
 * 3. Early Exit: Using 'return' inside a loop to immediately terminate the program.
 * 4. Error Exit Status: Returning a specific number (2) to indicate a data error.
 */

#include <stdio.h>

int main()
{
    float latitude;
    float longitude;
    char info[80];
    int started = 0;

    puts("data=[");
    while (scanf("%f,%f,%79[^\n]", &latitude, &longitude, info) == 3) {
        if (started)
            printf(",\n");
        else
            started = 1;

        // Check if latitude is outside the valid range (-90 to 90)
        if ((latitude < -90.0) || (latitude > 90.0)) {
            // Print error message to standard error (or stdout depending on context)
            printf("Invalid latitude: %f\n", latitude);
            // Exit the program immediately with an error status of 2
            return 2; 
        }

        // Check if longitude is outside the valid range (-180 to 180)
        if ((longitude < -180.0) || (longitude > 180.0)) {
            // Print error message
            printf("Invalid longitude: %f\n", longitude);
            // Exit the program immediately with an error status of 2
            return 2;
        }

        // If data is valid, print the JSON formatted string
        printf("{latitude: %f, longitude: %f, info: '%s'}", latitude, longitude, info);
    }
    puts("\n]");
    return 0;
}
