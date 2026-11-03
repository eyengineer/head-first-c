/*
 * PURPOSE:
 * This file will be compiled into a dynamic library (.so).
 * It calculates and prints the calories based on weight, distance, and a coefficient.
 */
#include <stdio.h>
#include "hfcal.h"

void display_calories(float weight, float distance, float coeff)
{
    // %3.2f means: print a float with 2 decimal places.
    printf("Weight: %3.2f lbs\n", weight);
    printf("Distance: %3.2f miles\n", distance);
    // Calculate calories: coeff * weight * distance
    printf("Calories burned: %4.2f cal\n", coeff * weight * distance);
}
