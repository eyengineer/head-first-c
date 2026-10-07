#include <stdio.h>

// This variable is declared outside any function, so it lives in GLOBALS
int y= 1;

int main(){

	// This variable is declared inside main(), so it lives in the STACK
    int x = 4;

    // Print the value of x
    printf("x is %i\n" , x);
    // Print the memory address of x using the & operator
    printf("x is stored at %p\n", &x);

    // Print the memory address of y
    printf("Y is stored at %p\n", &y);

    return 0;


}
