/*
 * ============================================================================
 * PURPOSE:
 * This program demonstrates Interprocess Communication (IPC) using a pipe.
 * It creates a child process to run a Python script (rssgossip.py) that 
 * fetches news URLs. The child writes these URLs into a pipe, and the parent 
 * process reads them from the pipe and opens them in a web browser.
 *
 * WHAT IT TEACHES:
 * 1. pipe(): Creating a unidirectional data channel between processes.
 * 2. dup2(): Redirecting Standard Output/Input to a pipe.
 * 3. close(): Why it is critical to close unused pipe ends to avoid deadlocks.
 * 4. execle(): Passing environment variables to a new process.
 * 5. fgets(): Reading data from a pipe as if it were a file.
 * ============================================================================
 */

#include <stdio.h>      // For printf, fprintf, fgets, sprintf
#include <stdlib.h>     // For exit(), system()
#include <unistd.h>     // For pipe(), fork(), dup2(), close(), execle()
#include <errno.h>      // For errno (error number)
#include <string.h>     // For strerror() (converts error to string)
#include <sys/types.h>  // For pid_t (process ID type)
#include <sys/wait.h>   // For waitpid()

// ============================================================================
// HELPER FUNCTION: error
// ============================================================================
// A "fire-and-forget" error handler. It prints the message, the system error,
// and exits the program immediately.
void error(char *msg)
{
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(1);
}

// ============================================================================
// HELPER FUNCTION: open_url
// ============================================================================
// This function opens a URL in the default web browser.
void open_url(char *url)
{
    char launch[255];
    // On Linux, "x-www-browser" opens the default browser.
    // The '&' at the end runs the browser in the background.
    sprintf(launch, "x-www-browser '%s' &", url);
    system(launch);
}

// ============================================================================
// MAIN FUNCTION
// ============================================================================
int main(int argc, char *argv[])
{
    // 1. The search phrase (e.g., "pajama death") comes from the command line.
    char *phrase = argv[1];
    
    // 2. Define environment variables for the Python script.
    // The RSS_FEED variable is crucial. If missing, Python throws a KeyError.
    char *vars[] = {"RSS_FEED=http://www.cnn.com/rss/celebs.xml", NULL};
    
    // ========================================================================
    // STEP 1: CREATE THE PIPE
    // ========================================================================
    // The pipe() function creates a one-way communication channel.
    // fd[0] -> Read end of the pipe.
    // fd[1] -> Write end of the pipe.
    int fd[2];
    if (pipe(fd) == -1) {
        error("Can't create the pipe");
    }

    // ========================================================================
    // STEP 2: FORK THE PROCESS
    // ========================================================================
    pid_t pid = fork();
    if (pid == -1) {
        error("Can't fork process");
    }

    // ========================================================================
    // STEP 3: CHILD PROCESS (The Writer)
    // ========================================================================
    if (!pid) { // Child process
        
        // 3a. Redirect Standard Output to the write end of the pipe.
        // Anything the child prints goes INTO the pipe.
        dup2(fd[1], 1);
        
        // 3b. Close the read end of the pipe.
        // The child doesn't read from the pipe. Leaving it open causes deadlocks.
        close(fd[0]);

        // 3c. Replace the child process with the Python script.
        // execl(path, arg0, arg1, arg2, arg3, NULL, environment)
        // - "/usr/bin/python3": The absolute path to Python.
        // - "python3": argv[0] for Python.
        // - "./rssgossip.py": The script to run.
        // - "-u": An argument for the script (show URLs).
        // - phrase: The search phrase.
        // - NULL: Marks the end of command-line arguments.
        // - vars: The environment variables (containing RSS_FEED).
        if (execle("/usr/bin/python3", "python3", "./rssgossip.py",
                   "-u", phrase, NULL, vars) == -1) {
            error("Can't run script");
        }
    }

    // ========================================================================
    // STEP 4: PARENT PROCESS (The Reader)
    // ========================================================================
    
    // 4a. Redirect Standard Input to the read end of the pipe.
    dup2(fd[0], 0);
    
    // 4b. Close the write end of the pipe.
    close(fd[1]);

    // 4c. Read lines from Standard Input (which is now the pipe).
    char line[255];
    while (fgets(line, 255, stdin)) {
        
        // 4d. The Python script outputs URLs preceded by a tab character ('\t').
        if (line[0] == '\t') {
            
            // 4e. Open the URL in the browser.
            // 'line + 1' skips the tab character.
            open_url(line + 1);
        }
    }

    return 0;
}
