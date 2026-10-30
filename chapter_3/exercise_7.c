/*
 * PURPOSE:
 * This program is an upgraded version of the 'categorize' tool.
 * Instead of hardcoding the search terms and output filenames, it reads them 
 * directly from the command line arguments using argc and argv.
 *
 * WHAT IT TEACHES:
 * 1. int main(int argc, char *argv[]): Receiving arguments from the terminal.
 * 2. Argument Validation: Checking if the user provided the correct number of arguments.
 * 3. Using argv: Accessing the strings passed by the user.
 * 4. fscanf(): Reading formatted data from a file stream.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    char line[80];

    // Check if the user provided exactly 5 arguments (plus the program name = 6)
    if (argc != 6) {
        fprintf(stderr, "You need to give 5 arguments\n");
        return 1;
    }

    // Open the input file in read mode
    FILE *in = fopen("spooky.csv", "r");
    
    // Open three output files using the filenames provided in the command line
    // argv[2], argv[4], and argv[5] are the strings for the file names
    FILE *file1 = fopen(argv[2], "w"); 
    FILE *file2 = fopen(argv[4], "w"); 
    FILE *file3 = fopen(argv[5], "w"); 

    // Read data from the input file using fscanf
    // fscanf reads from a FILE stream (unlike scanf which reads from keyboard)
    // "%79[^\n]\n": Read up to 79 chars until a newline, then consume the newline
    // The loop continues as long as exactly 1 item is successfully read
    while (fscanf(in, "%79[^\n]\n", line) == 1) {
        
        // Search for the first keyword (argv[1]) in the line
        if (strstr(line, argv[1])) {
            fprintf(file1, "%s\n", line);
        }
        // Search for the second keyword (argv[3]) in the line
        else if (strstr(line, argv[3])) {
            fprintf(file2, "%s\n", line);
        }
        // If neither keyword is found, write to the third file
        else {
            fprintf(file3, "%s\n", line);
        }
    }

    // Close all files to save data and free resources
    fclose(in);     // Don't forget to close the input file too!
    fclose(file1);
    fclose(file2);
    fclose(file3);

    return 0;
}
