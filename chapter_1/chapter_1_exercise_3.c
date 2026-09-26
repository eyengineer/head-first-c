/* Adding the libraries */
#include <stdio.h>
#include <stdlib.h>

/* Start the  main function */
int main(){

/* Describe  the variables */
   char card_name[3];
   int  val = 0;

/* Get input from the user */
   puts ("Enter the card mame: ");
   scanf("%2s", card_name);

/* Switch Case */
   switch (card_name[0]){
      case 'K':
      case 'Q': 
      case 'J':
         val = 10;
         break ;
      case 'A':
         val = 11;
         break;
      default :
         val = atoi(card_name);
         break;

    }
/*Cart Counting LOgic */
     if((val > 2 && val < 7)){
        puts("Counts has gone up");
    }else if (val == 10){
        puts("Counts has gone down");
    }
   return 0;
}
