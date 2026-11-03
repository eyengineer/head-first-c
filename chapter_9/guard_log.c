/*
 * ============================================================================
 * PURPOSE:
 * This program demonstrates how to use the system() function to append 
 * a timestamped comment to a log file. It's a simplified version of a 
 * security guard's check-in system.
 *
 * WHAT IT TEACHES:
 * 1. How to get the current time using <time.h>.
 * 2. How to format a string using sprintf().
 * 3. How to execute shell commands with system().
 * 4. The concept of Command Injection (and why system() is dangerous).
 * ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h> // Required for time() and asctime()

// ============================================================================
// FUNCTION: now
// ============================================================================
// Returns the current date and time as a formatted string.
char* now()
{
    // time_t is a special data type used to store time values (usually seconds since 1970).
    time_t t;
    
    // time(&t) asks the operating system for the current time and stores it in 't'.
    time(&t); 
    
    // localtime(&t) converts the raw time into a human-readable struct (year, month, etc.).
    // asctime() converts that struct into a string like "Thu Oct 29 11:25:53 2015\n".
    // The function returns a pointer to this string.
    return asctime(localtime(&t)); 
}

// ============================================================================
// MAIN FUNCTION
// ============================================================================
int main()
{
    char comment[80]; // Buffer to store the user's comment (max 79 chars + '\0')
    char cmd[120];    // Buffer to store the final shell command (max 119 chars + '\0')

    // 1. Read the user's comment from Standard Input (keyboard).
    // fgets() is used because it safely limits input to 80 characters, 
    // preventing buffer overflow. It also allows spaces in the comment.
    fgets(comment, 80, stdin);

    // 2. Build the shell command using sprintf().
    // sprintf() is like printf(), but instead of printing to the screen, 
    // it formats the text and stores it inside the 'cmd' string.
    //
    // THE COMMAND STRUCTURE:
    // echo ' <user_comment> <timestamp> ' >> reports.log
    //
    // - echo: A shell command that prints its arguments.
    // - '...': Single quotes ensure the whole comment is treated as one argument.
    // - %s: The first %s is replaced by 'comment'.
    // - %s: The second %s is replaced by the result of now().
    // - >>: The double greater-than operator APPENDS the output to a file 
    //       (rather than overwriting it with a single >).
    // - reports.log: The target file.
    sprintf(cmd, "echo '%s %s' >> reports.log", comment, now());

    // 3. Execute the command using system().
    // system() passes the string 'cmd' to the operating system's shell (like /bin/sh).
    // The shell then interprets the command and executes it.
    // WARNING: If 'comment' contains shell metacharacters (like && or ;), 
    // it can lead to Command Injection!
    system(cmd);

    return 0;
}
