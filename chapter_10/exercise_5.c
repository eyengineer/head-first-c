/*
 * ============================================================================
 * PURPOSE:
 * This program tests the user's math skills. It asks multiplication questions
 * and keeps track of the score. The program runs forever unless:
 * 1. The user presses Ctrl+C (SIGINT).
 * 2. The user takes more than 5 seconds to answer (SIGALRM).
 *
 * WHAT IT TEACHES:
 * 1. Signal handling: Combining SIGALRM (timer) and SIGINT (Ctrl+C).
 * 2. raise(): Sending a signal to yourself to trigger another handler.
 * 3. alarm(): Setting a timer that resets with each loop iteration.
 * ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <errno.h>
#include <signal.h>

// Global variable to keep track of the score.
int score = 0;

// ============================================================================
// SIGNAL HANDLER: end_game
// ============================================================================
// This function is called when SIGINT (Ctrl+C) is received.
// It displays the final score and exits the program.
void end_game(int sig)
{
    // Print the final score. %i is for integers.
    printf("\nFinal score: %i\n", score);
    
    // Set the exit status to 0 (success) and stop the program.
    exit(0);
}

// ============================================================================
// HELPER FUNCTION: catch_signal
// ============================================================================
// Registers a signal handler using sigaction.
int catch_signal(int sig, void (*handler)(int))
{
    struct sigaction action;
    action.sa_handler = handler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;
    return sigaction(sig, &action, NULL);
}

// ============================================================================
// SIGNAL HANDLER: times_up
// ============================================================================
// This function is called when SIGALRM (timer) is received.
// It tells the user time is up and then raises SIGINT to end the game.
void times_up(int sig)
{
    // Print a warning message.
    puts("\nTIME'S UP!");
    
    // Raising SIGINT will trigger the end_game() function.
    // This is called "Signal Escalation".
    raise(SIGINT);
}

// ============================================================================
// HELPER FUNCTION: error
// ============================================================================
// Handles errors and exits.
void error(char *msg)
{
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(1);
}

// ============================================================================
// MAIN FUNCTION
// ============================================================================
int main()
{
    // 1. Register the SIGALRM handler (time_is_up).
    catch_signal(SIGALRM, times_up);
    
    // 2. Register the SIGINT handler (end_game).
    catch_signal(SIGINT, end_game);
    
    // 3. Seed the random number generator with the current time.
    // This ensures different random numbers each time you run the program.
    srandom(time(0));
    
    // 4. Infinite loop: The game runs until a signal stops it.
    while (1) {
        // Generate two random numbers between 0 and 10.
        int a = random() % 11;
        int b = random() % 11;
        
        // Buffer to store the user's answer (max 3 chars + '\0').
        char txt[4];
        
        // 5. Set the alarm for 5 seconds.
        // This timer is reset in every loop iteration.
        // As long as the user answers within 5 seconds, the timer never fires.
        alarm(5);
        
        // Ask the multiplication question.
        printf("\nWhat is %i times %i? ", a, b);
        
        // Read the user's answer.
        fgets(txt, 4, stdin);
        
        // Convert the string answer to an integer.
        int answer = atoi(txt);
        
        // 6. Check if the answer is correct.
        if (answer == a * b)
            score++; // Increment score if correct.
        else
            printf("\nWrong! Score: %i\n", score); // Print score if wrong.
    }
    
    return 0;
}
