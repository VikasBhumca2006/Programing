#include "LinkList_Utility.h"

int main ()
{
    LinkList * listPtr = NULL;
    int arr[] = {8, 4, 12, 2, 6, 10, 14, 1, 3, 5, 7, 9, 11, 13, 15, 17, 0};

    listPtr = Create_LinkList ( arr, 7 );


    Print_LinkList ( listPtr );

    printf ("[%d] ",removeStart ( &listPtr ));
    printf ("[%d] ",removeStart ( &listPtr ));
    printf ("[%d] ",removeStart ( &listPtr ));
    Print_LinkList ( listPtr );

    printf ("\n===============\n");

    listPtr = addStart ( listPtr, 61 );
    listPtr = addStart ( listPtr, 62 );
    listPtr = addStart ( listPtr, 63 );
    listPtr = addStart ( listPtr, 64 );

    printf ("\n===============\n");

    Print_LinkList ( listPtr );

    printf ("\n");
    return 0;
}
