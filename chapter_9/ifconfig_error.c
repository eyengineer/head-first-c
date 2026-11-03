/*
 * ============================================================================
 * PURPOSE:
 * This program tries to run a network configuration tool (/sbin/ifconfig).
 * If it fails, it tries to find it in the system's PATH (ifconfig).
 * If both fail, it prints a detailed error message using errno and strerror().
 *
 * WHAT IT TEACHES:
 * 1. execl(): Executes a program using its absolute path.
 * 2. execlp(): Executes a program by searching the PATH environment variable.
 * 3. errno: A global variable set by the OS when a system call fails.
 * 4. strerror(): Converts the error number in errno into a human-readable string.
 * ============================================================================
 */

#include <stdio.h>
#include <unistd.h> // Required for execl() and execlp()
#include <errno.h>  // Required for errno
#include <string.h> // Required for strerror()

int main()
{
    // 1. Try to execute /sbin/ifconfig using its absolute path.
    // The first argument is the path. The second is argv[0] (program name).
    // NULL marks the end of arguments.
    // If successful, the current process is replaced and this line never returns.
    // If it fails, it returns -1.
    if (execl("/sbin/ifconfig", "/sbin/ifconfig", NULL) == -1) {
        
        // 2. If the absolute path failed, try searching the PATH.
        // execlp() looks in directories like /bin, /usr/bin, etc.
        if (execlp("ifconfig", "ifconfig", NULL) == -1) {
            
            // 3. If both failed, print the error.
            // errno is set by the OS to indicate the type of error (e.g., 2 for ENOENT).
            // strerror(errno) translates that number into a readable message.
            fprintf(stderr, "Cannot run ifconfig: %s", strerror(errno));
            return 1; // Exit with an error code
        }
    }
    return 0; // This line is only reached if execl/execlp succeeds (which means it won't be reached)
}
