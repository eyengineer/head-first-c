/*
 * ============================================================================
 * PURPOSE:
 * This program demonstrates concurrent process creation using fork() and exec().
 * It reads a search phrase from the command line, and then searches multiple
 * RSS feeds (news sources) simultaneously by creating a separate child process 
 * for each feed.
 *
 * WHAT IT TEACHES:
 * 1. fork(): Cloning the current process (creating a child process).
 * 2. execlp(): Replacing the child process with a new program (the Python script).
 * 3. Environment variables: Passing dynamic variables to the new process.
 * 4. Process IDs (pid_t): Identifying parent and child processes.
 * ============================================================================
 */

#include <stdio.h>   // Standard I/O (printf, fprintf)
#include <stdlib.h>  // General utilities
#include <unistd.h>  // POSIX OS API (fork, execlp)
#include <errno.h>   // Error number definitions (errno)
#include <string.h>  // String manipulation (strerror)
#include <sys/types.h> // Data types used in system calls (pid_t)

int main(int argc, char *argv[])
{
    // 1. Define an array of RSS feed URLs.
    // Each string is a pointer to a web address containing news feeds.
    char *feeds[] = {
    "https://www.ntv.com.tr/son-dakika.rss",
    "https://www.bbc.com/turkce/index.xml",
    "https://www.hurriyet.com.tr/rss/anasayfa"

    };
    
    // 2. The number of feeds we want to process (3 in this case).
    int times = 3;
    
    // 3. The search phrase comes from the first command-line argument.
    // If you run "./newshound 'pajama death'", then phrase = "pajama death".
    char *phrase = argv[1];
    
    // Loop counter
    int i;

    // 4. Loop through each RSS feed.
    for (i = 0; i < times; i++) {
        
        // Buffer to hold the environment variable string (max 254 chars + '\0').
        char var[255];
        
        // 5. Format the environment string.
        // Example result: "RSS_FEED=http://www.cnn.com/rss/celebs.xml"
        // This string will be passed to the Python script.
        sprintf(var, "RSS_FEED=%s", feeds[i]);
        
        // 6. Create an array of strings for the environment.
        // It must be terminated by NULL.
        // The Python script reads 'RSS_FEED' to know which URL to fetch.
        char *vars[] = {var, NULL};

        // ====================================================================
        // THE MAGIC OF FORK() BEGINS HERE
        // ====================================================================
        // 7. Clone the current process.
        // After this line, TWO identical processes are running: 
        // the Parent and the Child.
        pid_t pid = fork();
        
        // 8. Check for fork failure.
        // If fork returns -1, it means the operating system couldn't create 
        // the child process (e.g., out of memory).
        if (pid == -1) {
            // Print the error message to Standard Error (stderr).
            // strerror(errno) converts the error code into a readable message.
            fprintf(stderr, "Can't fork process: %s\n", strerror(errno));
            return 1; // Exit the parent process with an error code.
        }
        
        // 9. Check if we are in the CHILD process.
        // If fork returns 0, this code is running in the newly created child.
        // If fork returns a positive number, this code is running in the parent.
        if (!pid) { // Same as: if (pid == 0)
            
            // 10. The child process replaces itself with the Python script.
            // execlp() searches the PATH for "python3".
            // Arguments: (program_name, arg0, arg1, arg2, ..., NULL, environment)
            // - "python3": The interpreter.
            // - "python3": argv[0] for Python.
            // - "rssgossip.py": The script to run.
            // - phrase: The search term passed as an argument to the script.
            // - NULL: Marks the end of command-line arguments.
            // - vars: The custom environment array (containing RSS_FEED).
            if (execle("/usr/bin/python3", "python3", "rssgossip.py", phrase, NULL, vars) == -1) {
                
                // If execlp fails, print the error and exit.
                // Note: This code only runs if the child FAILS to start the script.
                fprintf(stderr, "Can't run script: %s\n", strerror(errno));
                return 1;
            }
            // If execlp succeeds, the child process is completely replaced by Python.
            // It will never reach this line.
        }
        
        // 11. The parent process continues here.
        // The parent does NOT wait for the child to finish (no wait() call).
        // It immediately goes to the next iteration of the loop, 
        // creating a new child for the next feed.
    }
    // 12. The parent process exits the program.
    // The children might still be running in the background.
    return 0;
}
