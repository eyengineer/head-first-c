// Include the standard input/output library for printf
#include <stdio.h>

// Function definition: takes two integer pointers as arguments
// This means it receives the memory addresses of the original variables
int go_south_east(int *lat, int *lon){

    // Dereference the lat pointer to get the value, subtract 1, and store it back
    *lat = *lat - 1 ;
    // Dereference the lon pointer to get the value, add 1, and store it back
    *lon = *lon + 1 ;
}

int main(){
   int latitude = 32;
   int longitude = -64;

   // Call the function, passing the addresses of the variables using the & operator
   // This allows the function to modify the original variables
   go_south_east(&latitude, &longitude);

   // Print the updated values of latitude and longitude
   printf("Avast ! Now at : [%i, %i]\n", latitude, longitude);
   return 0 ;

}
