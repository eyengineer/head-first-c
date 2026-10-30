/*
 * PURPOSE:
 * This program reads data from a file (spooky.csv) line by line.
 * It categorizes each line based on its content and writes it to one of three 
 * different output files (ufos.csv, disappearances.csv, or others.csv).
 *
 * WHAT IT TEACHES:
 * 1. fopen(): Opening multiple file streams simultaneously.
 * 2. File Modes: Using "r" for reading and "w" for writing.
 * 3. fscanf(): Reading formatted text from a file stream.
 * 4. strstr(): Searching for a substring within a line of text.
 * 5. fclose(): Properly closing file streams to save data and free resources.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    // Buffer to hold each line read from the input file
    char line[80];

    // Open the input file in read ("r") mode
    FILE *in = fopen("spooky.csv", "r");
    
    // Open the three output files in write ("w") mode
    FILE *file1 = fopen("ufos.csv", "w");
    FILE *file2 = fopen("disappearances.csv", "w");
    FILE *file3 = fopen("others.csv", "w");

    // Check if the input file failed to open
    if (in == NULL) {
        fprintf(stderr, "Error: Could not open spooky.csv\n");
        return 1;
    }

    // Read each line from the input file until the end of file
    // %79[^\n]\n reads up to 79 characters until a newline, then consumes the newline
    while (fscanf(in, "%79[^\n]\n", line) == 1) {
        
        // Check if the line contains the word "UFO"
        if (strstr(line, "UFO")) {
            // Write the line to the UFO file
            fprintf(file1, "%s\n", line);
        }
        // Check if the line contains the word "Disappearance"
        else if (strstr(line, "Disappearance")) {
            // Write the line to the Disappearance file
            fprintf(file2, "%s\n", line);
        }
        // If neither, it goes to the "others" file
        else {
            fprintf(file3, "%s\n", line);
        }
    }

    // Close the input stream
    fclose(in);
    // Close all output streams to ensure data is saved
    fclose(file1);
    fclose(file2);
    fclose(file3);

    return 0;
}
