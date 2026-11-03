/*
 * ============================================================================
 * PURPOSE:
 * This program tests the coffee program by passing it a custom environment
 * variable (FOOD=coffee) and a command-line argument ("donuts") using execle().
 *
 * WHAT IT TEACHES:
 * 1. execle(): Replacing the current process with a new one, while passing
 *    a custom array of environment variables.
 * 2. Environment array format: An array of strings in "KEY=value" format, 
 *    terminated by NULL.
 * ============================================================================
 */

#include <stdio.h>
#include <unistd.h> // Required for execle()

int main()
{
    // 1. Create a custom environment array.
    // "FOOD=coffee" sets the FOOD variable to "coffee".
    // NULL marks the end of the environment array.
    char *my_env[] = {"FOOD=coffee", NULL};
    
    // 2. Execute the "./coffee" program using execle().
    // Arguments: (path, arg0, arg1, ..., NULL, environment_array)
    // - "./coffee": The path to the program.
    // - "./coffee": The name of the program (argv[0]).
    // - "donuts": The first argument (argv[1]).
    // - NULL: Marks the end of the argument list.
    // - my_env: The custom environment variables.
    if (execl("./coffee", "./coffee", "donuts", NULL, my_env) == -1) {
        fprintf(stderr, "Error!\n");
        return 1;
    }
    return 0;
}
