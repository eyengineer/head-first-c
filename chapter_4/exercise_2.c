/*
 * PURPOSE:
 * This program demonstrates the size and limits of fundamental C data types.
 * It uses the <limits.h> and <float.h> headers to find the maximum and minimum 
 * values that 'int' and 'float' can hold, and uses sizeof() to find their memory sizes.
 *
 * WHAT IT TEACHES:
 * 1. Header Files for Limits: Using <limits.h> for integers and <float.h> for floats.
 * 2. Macros: INT_MAX, INT_MIN, FLT_MAX, FLT_MIN.
 * 3. sizeof() operator: Finding out how many bytes a data type takes in memory.
 * 4. Data Representation: Understanding that floats have a massive range but limited precision.
 */

#include <stdio.h>
#include <limits.h> // Contains limits for integer types (like INT_MAX, INT_MIN)
#include <float.h>  // Contains limits for floating-point types (like FLT_MAX, FLT_MIN)

int main()
{
    // Print the maximum and minimum values an integer can hold on this machine
    printf("The value of INT_MAX is %i\n", INT_MAX);
    printf("The value of INT_MIN is %i\n", INT_MIN);
    
    // Use sizeof() to find out how many bytes an int occupies in memory
    printf("An int takes %zu bytes\n", sizeof(int));

    // Print the maximum and minimum values a float can hold
    // Notice %f is used for floats, and %e or %f for scientific notation/extremes
    printf("The value of FLT_MAX is %f\n", FLT_MAX);
    printf("The value of FLT_MIN is %.50f\n", FLT_MIN);
    
    // Use sizeof() to find out how many bytes a float occupies in memory
    printf("A float takes %zu bytes\n", sizeof(float));

    return 0;
}
