/*
 * PURPOSE:
 * The main program that uses our dynamic library.
 * It calls display_calories with test data (115.2 lbs, 11.3 miles).
 */
#include <stdio.h>
#include "hfcal.h"

int main()
{
    display_calories(115.2, 11.3, 0.79);
    return 0;
}
