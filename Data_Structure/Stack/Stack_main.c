#include "Stack_Utility.h"

int main ()
{
    Stack * sPtr = NULL;
    int arr[] = {8, 4, 12, 2, 6, 10, 14, 1, 3, 5, 7, 9, 11, 13, 15, 17, 0};

    sPtr = Create_Stack ( arr, 7 );


    Print_Stack ( sPtr );

    printf ("[%d] ",pop ( &sPtr ));
    printf ("[%d] ",pop ( &sPtr ));
    printf ("[%d] ",pop ( &sPtr ));
    Print_Stack ( sPtr );

    printf ("\n===============\n");

    sPtr = push ( sPtr, 61 );
    sPtr = push ( sPtr, 62 );
    sPtr = push ( sPtr, 63 );
    sPtr = push ( sPtr, 64 );

    printf ("\n===============\n");

    Print_Stack ( sPtr );

    printf ("\n");
    return 0;
}
