#include "Queue_Utility.h"

int main ()
{
    mem_init();
    logger_init();

    Queue * qPtr = NULL;
    int arr[] = {8, 4, 12, 2, 6, 10, 14, 1, 3, 5, 7, 9, 11, 13, 15, 17, 0};

    printf ("\n===============\n");
    qPtr = Create_Queue ( arr, 7 );

    printf ("\n===============\n");

    Print_Queue ( qPtr );

    printf ("\n===============\n");

    printf ("[%d] ",dequeue ( &qPtr ));
    printf ("[%d] ",dequeue ( &qPtr ));
    printf ("[%d] ",dequeue ( &qPtr ));

    printf ("\n");
    Print_Queue ( qPtr );


    qPtr = enqueue ( qPtr, 61 );
    qPtr = enqueue ( qPtr, 62 );
    qPtr = enqueue ( qPtr, 63 );
    qPtr = enqueue ( qPtr, 64 );

    printf ("\n===============\n");

    Print_Queue ( qPtr );

    printf ("\n");
    return 0;
}
