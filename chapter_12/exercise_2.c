/*
 * ============================================================================
 * PURPOSE:
 * This program demonstrates a "Race Condition". It creates 20 threads, 
 * each trying to reduce the global 'beers' variable by 100,000.
 * Because they access the shared variable without any protection (mutex),
 * the final result is unpredictable and usually NOT zero.
 *
 * WHAT IT TEACHES:
 * 1. Global variables shared across threads.
 * 2. pthread_create() and pthread_join() inside a loop.
 * 3. Why shared data without locks causes data corruption (Race Condition).
 * ============================================================================
 */

#include <stdio.h>      // For printf
#include <stdlib.h>     // For exit
#include <pthread.h>    // Required for pthread_create, pthread_join, pthread_t

// ============================================================================
// GLOBAL VARIABLE: beers
// ============================================================================
// This variable is shared by ALL threads. 
// Every thread will read from and write to this exact same memory location.
int beers = 2000000;

// ============================================================================
// THREAD FUNCTION: drink_lots
// ============================================================================
// This is the function that each of the 20 threads will execute.
// It takes a void* (required by pthread) and returns a void*.
void* drink_lots(void *a)
{
    int i;
    // Each thread tries to reduce the beer count by 100,000.
    // This loop is the "Critical Section" where the Race Condition happens.
    for (i = 0; i < 100000; i++) {
        
        // THE PROBLEM LINE:
        // This is NOT a single atomic operation. It consists of:
        // 1. Read the current value of 'beers' from RAM.
        // 2. Subtract 1 from that value.
        // 3. Write the new value back to RAM.
        // If two threads do this at the same time, they might read the same
        // value, subtract 1, and write it back, causing a lost update.
        beers = beers - 1;
    }
    // Return NULL because the thread doesn't need to return a value.
    return NULL;
}

// ============================================================================
// MAIN FUNCTION
// ============================================================================
int main()
{
    // 1. Array to hold the IDs of 20 threads.
    // 'pthread_t' is the data type used to store thread identifiers.
    pthread_t threads[20];
    
    // Loop counter for creating and joining threads.
    int t;
    
    // Print the initial number of beers.
    printf("%i bottles of beer on the wall\n%i bottles of beer\n", beers, beers);

    // ========================================================================
    // STEP 1: CREATE 20 THREADS
    // ========================================================================
    for (t = 0; t < 20; t++) {
        // pthread_create() takes 4 arguments:
        // 1. &threads[t]: Pointer to store the thread ID.
        // 2. NULL: Default thread attributes.
        // 3. drink_lots: The function the thread will run.
        // 4. NULL: Argument to pass to the function (none here).
        pthread_create(&threads[t], NULL, drink_lots, NULL);
    }

    // Variable to store the return value of the threads (we don't use it here).
    void* result;

    // ========================================================================
    // STEP 2: WAIT FOR ALL 20 THREADS TO FINISH
    // ========================================================================
    for (t = 0; t < 20; t++) {
        // pthread_join() pauses the main program until the thread finishes.
        // We must join all threads, otherwise the program might exit before
        // they finish their work.
        pthread_join(threads[t], &result);
    }

    // ========================================================================
    // STEP 3: PRINT THE FINAL RESULT
    // ========================================================================
    // Theoretically, 20 threads * 100,000 beers = 2,000,000 beers.
    // So this SHOULD print 0.
    // But because of the Race Condition, it will print a random number.
    printf("There are now %i bottles of beer on the wall\n", beers);

    return 0;
}
