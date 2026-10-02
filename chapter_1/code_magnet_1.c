#include  <stdio.h>
#include  <stdlib.h>

/*Entry point of the program. Every C program starts from main.  */
int main()
{
/* Declares a character array named card_name with 3 elements.  */
    char card_name[3];
    puts("Enter the card_name: ");
/*Reads at most 2 characters from the user and stores them in card_name. */
    scanf("%2s", card_name);
    int  val = 0 ;
    if (card_name[0]=='K'){
        val = 10 ;
    }else if (card_name[0]=='Q') {
        val= 10;
    }else if (card_name[0]=='J') {
        val =10;
    
    }else if (card_name[0]=='A'){
        val =11 ;
    }else {
/*This converts the text into a number.(atoi) */
        val = atoi (card_name); 
    }
printf("The card value is : %i\n",val);

/*Prints the value of val to the screen.

    %i: A placeholder for an integer. i = integer.

    \n: Newline.

    val: The variable to be printed in place of %i.  */
return 0;
}

