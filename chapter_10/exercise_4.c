/*
 * ============================================================================
 * PURPOSE:
 * This program demonstrates how to use the alarm() function and signal 
 * handlers together. It sets an alarm for 5 seconds. If the user doesn't 
 * enter their name within 5 seconds, the SIGALRM signal is triggered, and 
 * the program exits with a custom message.
 *
 * WHAT IT TEACHES:
 * 1. alarm(): Setting a timer for the process.
 * 2. SIGALRM: The signal sent when the timer expires.
 * 3. Signal handling: Catching SIGALRM and running custom code.
 * 4. Interruption: How signals interrupt blocking functions like fgets().
 * ============================================================================
 */

#include <stdio.h>      // For printf, fprintf, fgets
#include <stdlib.h>     // For exit()
#include <signal.h>     // For sigaction, SIGALRM, sigemptyset
#include <unistd.h>     // For alarm()

// ============================================================================
// CUSTOM SIGNAL HANDLER: time_is_up
// ============================================================================
// This function will be called when the SIGALRM signal is received.
// It takes the signal number as an argument (int sig).
void time_is_up(int sig)
{
    // Print a message to Standard Output.
    // We use '\n' to ensure the message appears on a new line.
    puts("\nTime is up! You took too long.");
    
    // Exit the program with an error code (1).
    // This prevents the program from continuing after the alarm.
    exit(1);
}

// ============================================================================
// HELPER FUNCTION: catch_signal
// ============================================================================
// This function wraps the complex sigaction setup into a simple call.
// It registers a handler for a specific signal.
// Parameters:
// - sig: The signal number (e.g., SIGALRM).
// - handler: A pointer to the function to call when the signal arrives.
int catch_signal(int sig, void (*handler)(int))
{
    // Create a new sigaction structure.
    struct sigaction action;
    
    // Set the handler function to the one provided.
    action.sa_handler = handler;
    
    // Initialize the signal mask to empty (no signals are blocked).
    sigemptyset(&action.sa_mask);
    
    // Set flags to 0 (default behavior).
    action.sa_flags = 0;
    
    // Register the action with the operating system.
    return sigaction(sig, &action, NULL);
}

// ============================================================================
// MAIN FUNCTION
// ============================================================================
int main()
{
    // 1. Register the SIGALRM handler.
    // If catch_signal fails, print an error and exit.
    if (catch_signal(SIGALRM, time_is_up) == -1) {
        fprintf(stderr, "Can't map the handler\n");
        exit(2);
    }

    // 2. Set the alarm for 5 seconds.
    // The operating system will start a countdown.
    alarm(5);

    // Prompt the user for their name.
    char name[30];
    printf("Enter your name (you have 5 seconds): ");
    
    // 3. Wait for input.
    // If the user types their name and presses Enter before 5 seconds,
    // fgets() returns and the program continues.
    // If 5 seconds pass, the alarm fires, SIGALRM is triggered,
    // and the time_is_up() function is called.
    fgets(name, 30, stdin);
    
    // 4. If the user was fast enough, we reach here.
    printf("Hello %s\n", name);
    
    return 0;
}
