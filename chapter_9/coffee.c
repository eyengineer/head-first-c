/*
 * ============================================================================
 * PURPOSE:
 * This is the "coffee" program used in the Mixed Messages exercise.
 * It generates an order string by checking environment variables and 
 * command-line arguments in a specific order of priority.
 *
 * WHAT IT TEACHES:
 * 1. getenv(): Reading environment variables.
 * 2. Priority logic: Checking "EXTRA" first, then "FOOD", then command-line args.
 * 3. argv[argc - 1]: Accessing the last command-line argument.
 * ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // 1. Try to get the "EXTRA" environment variable.
    // If it doesn't exist, try "FOOD".
    // If that doesn't exist either, use the last command-line argument.
    char *w = getenv("EXTRA");
    if (!w) w = getenv("FOOD");
    if (!w) w = argv[argc - 1];
    
    // 2. Do the same for the second part of the order (c).
    char *c = getenv("EXTRA");
    if (!c) c = argv[argc - 1];
    
    // 3. Print the final combination.
    printf("%s with %s\n", c, w);
    return 0;
}
