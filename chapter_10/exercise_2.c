/*
 * ============================================================================
 * PURPOSE:
 * This program fetches RSS news stories using a Python script and saves them
 * to a file called "stories.txt". It uses `execle` to pass environment 
 * variables and `waitpid` to ensure the parent process waits for the child 
 * to finish before exiting.
 *
 * WHAT IT TEACHES:
 * 1. Process Creation: Using fork() to create a child process.
 * 2. Redirection: Using dup2() and fileno() to redirect output to a file.
 * 3. Environment Variables: Using execle() to pass custom environment variables.
 * 4. Synchronization: Using waitpid() to prevent the parent from exiting too early.
 * ============================================================================
 */

#include <stdio.h>      // For printf, fprintf, fopen, fileno
#include <stdlib.h>     // For exit()
#include <unistd.h>     // For fork(), dup2(), execle()
#include <errno.h>      // For errno (error number)
#include <string.h>     // For strerror() (converts error to string)
#include <sys/types.h>  // For pid_t (process ID type)
#include <sys/wait.h>   // For waitpid() (waiting for child process)

// ============================================================================
// HELPER FUNCTION: error
// ============================================================================
// This function is a "fire-and-forget" error handler.
// It prints the custom message, the system error string, and exits immediately.
void error(char *msg)
{
    // %s is replaced by 'msg' (our custom message).
    // strerror(errno) converts the current error number into a readable string.
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    
    // exit(1) terminates the program instantly with an error code.
    exit(1);
}

// ============================================================================
// MAIN FUNCTION
// ============================================================================
int main(int argc, char *argv[])
{
    // 1. The search phrase is passed as the first command-line argument.
    // Example: If run as "./exercise_2 'pajama death'", argv[1] is "pajama death".
    char *phrase = argv[1];
    
    // 2. Define the environment variable for the Python script.
    // The RSS_FEED variable tells the script which URL to fetch.
    // It must be terminated by NULL.
    char *vars[] = {"RSS_FEED=http://www.cnn.com/rss/celebs.xml", NULL};
    
    // 3. Open the file "stories.txt" in write mode ("w").
    // If the file doesn't exist, it creates it. If it exists, it overwrites it.
    FILE *f = fopen("stories.txt", "w");
    
    // 4. Check if the file was opened successfully.
    // fopen returns NULL on failure (e.g., permission denied or disk full).
    if (!f) {
        error("Can't open stories.txt");
    }

    // 5. Create a child process using fork().
    // After this line, two identical processes are running: Parent and Child.
    pid_t pid = fork();
    
    // 6. Check if fork failed.
    // fork() returns -1 if it couldn't create the child process.
    if (pid == -1) {
        error("Can't fork process");
    }

    // 7. Check if we are in the CHILD process.
    // fork() returns 0 to the child process. '!pid' is the same as 'pid == 0'.
    if (!pid) {
        
        // 8. REDIRECTION MAGIC:
        // fileno(f) gets the integer file descriptor of our open file.
        // dup2(..., 1) copies that descriptor onto fd 1 (Standard Output).
        // Now, anything the child writes to stdout will go to stories.txt.
        if (dup2(fileno(f), 1) == -1) {
            error("Can't redirect Standard Output");
        }

        // 9. Replace the child process with the Python script using execle().
        // Arguments: (path, arg0, arg1, arg2, NULL, environment)
        // - "/usr/bin/python3": The absolute path to the Python interpreter.
        // - "python3": The name of the program (argv[0]).
        // - "./rssgossip.py": The script to run.
        // - phrase: The search term passed as an argument to the script.
        // - NULL: Marks the end of command-line arguments.
        // - vars: The custom environment array (containing RSS_FEED).
        if (execle("/usr/bin/python3", "python3", "./rssgossip.py", 
                   phrase, NULL, vars) == -1) {
            error("Can't run script");
        }
        // If execle succeeds, the child process is replaced by Python.
        // The code below this line is NEVER reached in the child process.
    }

    // ========================================================================
    // THE FIX: PARENT WAITS FOR THE CHILD
    // ========================================================================
    // 10. The parent process reaches this line.
    // waitpid() pauses the parent until the child process (pid) finishes.
    // &pid_status stores the exit status of the child.
    // 0 means "wait until the child terminates".
    int pid_status;
    if (waitpid(pid, &pid_status, 0) == -1) {
        error("Error waiting for child process");
    }

    // 11. The parent process exits only after the child has finished writing.
    return 0;
}
