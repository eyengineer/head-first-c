/*
 * PURPOSE:
 * This program uses nested 'if' statements to filter GPS coordinates.
 * It specifically looks for coordinates that fall within the "Bermuda Triangle" 
 * region (a specific latitude and longitude range) and only prints those.
 *
 * WHAT IT TEACHES:
 * 1. Nested Conditions: Using an 'if' statement inside another 'if' statement.
 * 2. Logical AND (&&): Ensuring BOTH conditions (e.g., lat > 26 AND lat < 34) are true.
 * 3. Filtering Data: Reading a stream of data but only acting on a specific subset.
 */

#include <stdio.h>

int main()
{
    float latitude;
    float longitude;
    char info[80];

    // Read the data from standard input (or redirected file)
    while (scanf("%f,%f,%79[^\n]", &latitude, &longitude, info) == 3) {
        
        // First check: Is the latitude roughly between 26 and 34?
        if ((latitude > 26) && (latitude < 34)) {
            
            // Second check (nested): Is the longitude roughly between -76 and -64?
            // If both latitude AND longitude match, we are in the target area.
            if ((longitude > -76) && (longitude < -64)) {
                
                // Print the filtered data
                printf("%f,%f,%s\n", latitude, longitude, info);
            }
        }
    }

    return 0;
}
