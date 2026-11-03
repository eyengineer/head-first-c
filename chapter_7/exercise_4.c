/*
 * ============================================================================
 * TOPIC: QSORT AND FUNCTION POINTERS (C STANDARD LIBRARY)
 * ============================================================================
 * 
 * PURPOSE:
 * This program demonstrates how to use the qsort() function from the C Standard Library.
 * It shows how to sort different data types (integers, strings, structs) 
 * by passing custom comparator functions.
 * 
 * WHAT IT TEACHES:
 * 1. qsort(): How to use the built-in Quick Sort algorithm.
 * 2. Comparator Functions: How to define the sorting rules (ascending, descending).
 * 3. void* (Void Pointers): How qsort can sort ANY data type by using generic pointers.
 * 4. Type Casting: Converting void* back to its original type inside the comparator.
 * ============================================================================
 */

#include <stdio.h>
#include <stdlib.h> // Required for qsort()
#include <string.h> // Required for strcmp()

// ============================================================================
// DATA STRUCTURE
// ============================================================================
// A simple struct to test sorting by area.
typedef struct {
    int width;  // Width of the rectangle
    int height; // Height of the rectangle
} rectangle;

// ============================================================================
// COMPARATOR FUNCTIONS (The Rules of Sorting)
// ============================================================================
// qsort() requires a function that takes two const void* parameters.
// The return value is crucial:
// < 0 (Negative) : The first argument goes BEFORE the second.
// > 0 (Positive) : The first argument goes AFTER the second.
// = 0           : They are equal, no swap needed.

// 1. SORT INTEGERS: SMALLEST TO LARGEST
int compare_scores(const void* score_a, const void* score_b)
{
    // qsort passes void* pointers. We must cast them to int* and dereference them (*)
    // to get the actual integer values.
    int a = *(int*)score_a;
    int b = *(int*)score_b;
    
    // If a > b, (a - b) is positive, so 'a' goes after 'b'.
    // If a < b, (a - b) is negative, so 'a' goes before 'b'.
    return a - b; 
}

// 2. SORT INTEGERS: LARGEST TO SMALLEST (DESCENDING)
int compare_scores_desc(const void* score_a, const void* score_b)
{
    int a = *(int*)score_a;
    int b = *(int*)score_b;
    
    // By subtracting 'a' from 'b' instead of 'b' from 'a', we reverse the logic.
    return b - a; 
}

// 3. SORT RECTANGLES: SMALLEST AREA TO LARGEST AREA
int compare_areas(const void* a, const void* b)
{
    // Cast the void pointers to rectangle pointers.
    const rectangle* ra = (const rectangle*)a;
    const rectangle* rb = (const rectangle*)b;
    
    // Calculate the areas using the -> operator.
    int area_a = (ra->width * ra->height);
    int area_b = (rb->width * rb->height);
    
    // Return the difference of the areas.
    return area_a - area_b;
}

// 4. SORT STRINGS: ALPHABETICAL ORDER (A to Z)
int compare_names(const void* a, const void* b)
{
    // IMPORTANT: An array of strings is an array of char pointers.
    // qsort passes the address of the array elements. 
    // Therefore, 'a' and 'b' are pointers to char pointers (char**).
    char** sa = (char**)a;
    char** sb = (char**)b;
    
    // Dereference (*sa, *sb) to get the actual strings, then use strcmp.
    // strcmp returns < 0 if sa is alphabetically before sb.
    return strcmp(*sa, *sb); 
}

// 5. SORT RECTANGLES: LARGEST AREA TO SMALLEST
int compare_areas_desc(const void* a, const void* b)
{
    // GENIUS TRICK: Instead of writing new logic, call the ascending function 
    // but swap the parameters (b, a). This reverses the order.
    return compare_areas(b, a);
}

// 6. SORT STRINGS: REVERSE ALPHABETICAL ORDER (Z to A)
int compare_names_desc(const void* a, const void* b)
{
    return compare_names(b, a);
}

// ============================================================================
// MAIN FUNCTION
// ============================================================================
int main()
{
    // --- TEST 1: SORTING INTEGERS ---
    int scores[] = {543, 323, 32, 554, 11, 3, 112};
    int num_scores = 7;
    int i;

    // qsort Parameters:
    // 1. The array to sort.
    // 2. Number of elements.
    // 3. Size of each element (sizeof(int)).
    // 4. The comparator function.
    qsort(scores, num_scores, sizeof(int), compare_scores_desc);
    
    puts("Scores sorted (Descending):");
    for (i = 0; i < num_scores; i++) {
        printf("Score = %i\n", scores[i]);
    }

    // --- TEST 2: SORTING STRINGS ---
    char *names[] = {"Karen", "Mark", "Brett", "Molly"};
    int num_names = 4;

    // NOTE: When sorting an array of strings, the size of each element 
    // is sizeof(char*) because the array holds pointers, not the actual text.
    qsort(names, num_names, sizeof(char*), compare_names);
    
    puts("\nNames sorted (Alphabetical):");
    for (i = 0; i < num_names; i++) {
        printf("%s\n", names[i]);
    }

    return 0;
}
