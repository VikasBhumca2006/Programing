#include "Queue_Utility.h"

Queue * Create_Queue ( int *array, int size )
{
    Queue * qPtr = NULL;
    int idx = 0;

    for ( idx = 0; idx < size; idx++ )
    {
        qPtr = enqueue ( qPtr, array[idx] );
    }

    return qPtr;
}

Queue * Create_Node ( int data )
{
    Queue * ptr = ( Queue * ) malloc ( sizeof(Queue) );
    if ( ptr )
    {
        ptr->data = data;
        ptr->next = NULL;
        return ptr;
    }
    return NULL;
}

Queue * enqueue ( Queue *qPtr, int data )
{
    Queue * tmp = qPtr;
    qPtr = Create_Node ( data );
    qPtr->next = tmp;
    return qPtr;
}

int dequeue ( Queue **qPtr )
{

    int data = -1;
    Queue * tmp = *qPtr;

    printf ("\n Dequeue ");

    if ( !isEmpty (tmp) )
    {

        if ( !tmp->next )
        {
            data = tmp->data;
            free ( tmp );
            *qPtr = NULL;
        }
        else
        {

            while ( tmp->next->next )
            {
                tmp = tmp->next;
            }

            data = tmp->next->data;
            free ( tmp->next );
            tmp->next = NULL;
        }
    }

    return data ;
}

bool isEmpty (Queue * qPtr )
{
    return ( qPtr == NULL );
}

void Print_Queue ( Queue * qPtr )
{
    if ( NULL == qPtr )
    {
        printf ( "|\n");
        return;
    }

    printf ( "| %d ", qPtr->data );

    Print_Queue ( qPtr->next );
}

