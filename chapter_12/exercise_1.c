/*
 * ============================================================================
 * PURPOSE:
 * This program demonstrates how to create two threads using the POSIX 
 * pthread library. Each thread runs a separate function that prints a message
 * 5 times with a 1-second delay. The two threads run in parallel.
 *
 * WHAT IT TEACHES:
 * 1. pthread_create(): Creating a new thread.
 * 2. pthread_join(): Waiting for a thread to finish before the main program ends.
 * 3. Thread functions: They must return a void* and take a void* argument.
 * 4. Compiling with -lpthread: Linking the pthread library.
 * ============================================================================
 */

#include <stdio.h>      // For printf, fprintf, puts
#include <stdlib.h>     // For exit
#include <string.h>     // For strerror
#include <unistd.h>     // For sleep()
#include <errno.h>      // For errno
#include <pthread.h>    // REQUIRED for pthread_create, pthread_join, pthread_t

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
// THREAD FUNCTION 1: does_not
// ============================================================================
// This function will run inside Thread A.
// Thread functions MUST have the signature: void* function_name(void* arg)
// - The argument is a void pointer (can be anything).
// - The return type is a void pointer (can be anything).
void* does_not(void *a)
{
    int i = 0;
    // Loop 5 times.
    for (i = 0; i < 5; i++) {
        // sleep(1) pauses the thread for 1 second.
        // This simulates "doing work" and gives the other thread time to run.
        sleep(1); 
        
        // puts() prints a string to Standard Output.
        puts("Does not!"); 
    }
    // We don't need to return anything, so we return NULL.
    // The thread function MUST return a void*.
    return NULL;
}

// ============================================================================
// THREAD FUNCTION 2: does_too
// ============================================================================
// This function will run inside Thread B.
// It is identical to does_not, but prints "Does too!" instead.
void* does_too(void *a)
{
    int i = 0;
    for (i = 0; i < 5; i++) {
        sleep(1); 
        puts("Does too!"); 
    }
    return NULL;
}

// ============================================================================
// MAIN FUNCTION
// ============================================================================
int main(int argc, char *argv[])
{
    // 1. Declare two thread identifiers.
    // 'pthread_t' is an opaque data type that holds information about a thread.
    // We need one for each thread we want to create.
    pthread_t t0;
    pthread_t t1;

    // ========================================================================
    // STEP 2: CREATE THREAD A
    // ========================================================================
    // pthread_create() takes 4 arguments:
    // 1. &t0: A pointer to the pthread_t variable where the thread ID will be stored.
    // 2. NULL: Thread attributes (NULL means use defaults).
    // 3. does_not: The function the thread will execute.
    // 4. NULL: The argument to pass to the function (NULL means no argument).
    // Returns 0 on success, non-zero on failure.
    if (pthread_create(&t0, NULL, does_not, NULL) == -1) {
        error("Can't create thread t0");
    }

    // ========================================================================
    // STEP 3: CREATE THREAD B
    // ========================================================================
    // Same as above, but for Thread B using the does_too function.
    if (pthread_create(&t1, NULL, does_too, NULL) == -1) {
        error("Can't create thread t1");
    }

    // ========================================================================
    // STEP 4: WAIT FOR THREAD A TO FINISH
    // ========================================================================
    // If we don't call pthread_join, the main program might exit before 
    // the threads finish their work. When main exits, all threads are killed.
    // 
    // pthread_join() takes 2 arguments:
    // 1. t0: The thread ID to wait for.
    // 2. &result: A pointer to a void* where the thread's return value will be stored.
    void* result;
    if (pthread_join(t0, &result) == -1) {
        error("Can't join thread t0");
    }

    // ========================================================================
    // STEP 5: WAIT FOR THREAD B TO FINISH
    // ========================================================================
    if (pthread_join(t1, &result) == -1) {
        error("Can't join thread t1");
    }

    // ========================================================================
    // STEP 6: EXIT
    // ========================================================================
    // Both threads have finished. The main program can exit safely.
    return 0;
}
