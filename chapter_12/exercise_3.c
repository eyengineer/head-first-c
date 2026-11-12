/*
 * ============================================================================
 * PURPOSE:
 * This program fixes the Race Condition from the previous exercise by using
 * a Mutex (Mutual Exclusion). It creates 20 threads that reduce a global
 * 'beers' variable. The mutex ensures only one thread modifies 'beers' at a time.
 *
 * WHAT IT TEACHES:
 * 1. pthread_mutex_t: Declaring a mutex (lock).
 * 2. PTHREAD_MUTEX_INITIALIZER: Initializing the mutex.
 * 3. pthread_mutex_lock() / unlock(): Protecting the Critical Section.
 * ============================================================================
 */

#include <stdio.h>      // For printf
#include <stdlib.h>     // For exit
#include <pthread.h>    // REQUIRED for pthread_create, pthread_join, pthread_mutex_t

// ============================================================================
// GLOBAL VARIABLES
// ============================================================================
// 1. The shared variable that all threads will modify.
int beers = 2000000;

// 2. Declare a global mutex.
// 'beers_lock' will act as a traffic light for the 'beers' variable.
// PTHREAD_MUTEX_INITIALIZER is a macro that initializes the mutex properly.
// It MUST be global so all threads can see and use it.
pthread_mutex_t beers_lock = PTHREAD_MUTEX_INITIALIZER;

// ============================================================================
// THREAD FUNCTION: drink_lots (Version A)
// ============================================================================
// This function is executed by each of the 20 threads.
void* drink_lots(void *a)
{
    int i;
    
    // ========================================================================
    // CRITICAL SECTION START
    // ========================================================================
    // 3. LOCK: We call pthread_mutex_lock() to acquire the lock.
    // If the lock is free, the thread acquires it and continues.
    // If another thread holds the lock, this thread will BLOCK (wait) here
    // until the lock is released by the other thread.
    // This ensures ONLY ONE thread can execute the loop below at a time.
    pthread_mutex_lock(&beers_lock);
    
    // 4. This is the protected loop. 
    // Because the lock is held, no other thread can read or write to 'beers'
    // while this loop is running. The "Race Condition" is eliminated.
    for (i = 0; i < 100000; i++) {
        beers = beers - 1;
    }
    
    // 5. UNLOCK: We release the lock.
    // This signals to the operating system that the critical section is done,
    // and another waiting thread can now acquire the lock and enter.
    pthread_mutex_unlock(&beers_lock);
    
    // ========================================================================
    // CRITICAL SECTION END
    // ========================================================================
    
    // 6. Print the current value of beers.
    // This is outside the lock. We do this to see the progression.
    printf("beers = %i\n", beers);
    
    // Return NULL as required by the thread function signature.
    return NULL;
}

// ============================================================================
// MAIN FUNCTION
// ============================================================================
int main()
{
    // 7. Array to store the IDs of the 20 threads.
    pthread_t threads[20];
    int t;
    
    // Print the initial state.
    printf("2000000 bottles of beer on the wall\n2000000 bottles of beer\n");

    // ========================================================================
    // STEP 1: CREATE 20 THREADS
    // ========================================================================
    for (t = 0; t < 20; t++) {
        // Create a new thread.
        // It will execute the 'drink_lots' function.
        // The thread ID is stored in threads[t].
        pthread_create(&threads[t], NULL, drink_lots, NULL);
    }

    void* result;
    // ========================================================================
    // STEP 2: WAIT FOR ALL THREADS TO FINISH
    // ========================================================================
    for (t = 0; t < 20; t++) {
        // The main program waits here until thread 't' finishes.
        // This prevents the program from exiting before the threads are done.
        pthread_join(threads[t], &result);
    }

    // ========================================================================
    // STEP 3: PRINT FINAL RESULT
    // ========================================================================
    // Because we used a mutex, the result will now be exactly 0.
    printf("There are now %i bottles of beer on the wall\n", beers);

    return 0;
}
