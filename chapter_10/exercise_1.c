/*
 * ============================================================================
 * PURPOSE:
 * This program fetches RSS news stories using a Python script, but instead 
 * of printing the results to the screen, it redirects the output of the CHILD 
 * process to a file called "stories.txt". The parent process remains unaffected.
 *
 * WHAT IT TEACHES:
 * 1. fileno(): Getting the integer file descriptor of a FILE stream.
 * 2. dup2(): Duplicating a file descriptor to redirect data streams (stdout).
 * 3. fork() + exec(): Running a new program in a child process.
 * 4. error(): A helper function to handle errors and exit cleanly.
 * ============================================================================
 */

#include <stdio.h>    // For printf, fprintf, fopen, fileno
#include <stdlib.h>   // For exit()
#include <unistd.h>   // For fork(), dup2(), execle()
#include <errno.h>    // For errno (error number)
#include <string.h>   // For strerror() (converts error number to string)
#include <sys/types.h> // For pid_t (process ID type)

// ============================================================================
// HELPER FUNCTION: error
// ============================================================================
// This function is a "fire-and-forget" error handler.
// It prints the error message and the system error string (strerror), 
// then immediately terminates the program using exit(1).
void error(char *msg)
{
    // fprintf(stderr, ...) prints to Standard Error (fd 2).
    // %s is replaced by 'msg' (our custom message).
    // strerror(errno) converts the current error number into a readable string.
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    
    // exit(1) terminates the program instantly with an error code.
    // It does NOT return to the calling function like 'return 1' would.
    exit(1);
}

// ============================================================================
// MAIN FUNCTION
// ============================================================================
int main(int argc, char *argv[])
{
    // 1. Get the search phrase from the command line (e.g., "pajama death").
    char *phrase = argv[1];
    
    // 2. Define the environment variable array for the Python script.
    // The Python script reads RSS_FEED to know which URL to fetch.
    char *vars[] = {"RSS_FEED=http://www.cnn.com/rss/celebs.xml", NULL};
    
    // 3. Open the file "stories.txt" for writing ("w").
    // This returns a FILE pointer, which we store in 'f'.
    FILE *f = fopen("stories.txt", "w");
    
    // 4. Check if fopen failed. If 'f' is NULL, the file couldn't be opened.
    if (!f) {
        // Call our error function. It will print the message and exit.
        error("Can't open stories.txt");
    }

    // 5. Clone the current process using fork().
    // After this line, TWO identical processes exist: Parent and Child.
    pid_t pid = fork();
    
    // 6. Check if fork failed. fork() returns -1 on failure.
    if (pid == -1) {
        error("Can't fork process");
    }

    // 7. Check if we are in the CHILD process.
    // fork() returns 0 to the child process.
    // '!pid' is the same as 'pid == 0'.
    if (!pid) {
        
        // 8. REDIRECTION MAGIC:
        // fileno(f) gets the integer file descriptor of our open file.
        // dup2(..., 1) takes that descriptor and makes it a copy of fd 1 (stdout).
        // Now, fd 1 points to "stories.txt" instead of the screen!
        if (dup2(fileno(f), 1) == -1) {
            // If dup2 fails, we call error and exit.
            error("Can't redirect Standard Output");
        }

        // 9. Execute the Python script using execle().
        // Because we redirected fd 1 in step 8, everything this script prints
        // will now go into "stories.txt" instead of the screen.
        // Arguments: (path, arg0, arg1, arg2, NULL, environment)
        if (execle("/usr/bin/python3", "python3", "./rssgossip.py", 
                   phrase, NULL, vars) == -1) {
            // If execle fails, print error and exit.
            error("Can't run script");
        }
        // If execle succeeds, the child process is replaced by Python, 
        // and this line is never reached.
    }

    // 10. The PARENT process continues here.
    // The parent's stdout is still connected to the screen (fd 1).
    // The parent can do other things while the child fetches the news.
    return 0;
}
