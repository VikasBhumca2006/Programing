#include "Stack_Utility.h"

Stack * Create_Stack ( int *array, int size )
{
    Stack * sPtr = NULL;
    int idx = 0;

    for ( idx = 0; idx < size; idx++ )
    {
        sPtr = push ( sPtr, array[idx] );
    }

    return sPtr;
}

Stack * Create_Node ( int data )
{
    Stack * ptr = ( Stack * ) malloc ( sizeof(Stack) );
    if ( ptr )
    {
        ptr->data = data;
        ptr->next = NULL;
        return ptr;
    }
    return NULL;
}

Stack * push ( Stack *sPtr, int data )
{
    Stack * tmp = sPtr;
    sPtr = Create_Node ( data );
    sPtr->next = tmp;
    return sPtr;
}

int pop ( Stack **sPtr )
{

    printf ("\n Pop ");

    if ( isEmpty (*sPtr) )
        return -1;

    Stack * tmp = *sPtr;
    int data = tmp->data;

    *sPtr = tmp->next;
    free ( tmp );

    return data ;
}

bool isEmpty (Stack * sPtr )
{
    return ( sPtr == NULL );
}

void Print_Stack ( Stack * sPtr )
{
    if ( NULL == sPtr )
        return;

    if ( sPtr->data > 9 )
        printf ( "\n\t |   %d  |", sPtr->data );
    else
        printf ( "\n\t |   %d   |", sPtr->data );

    printf ( "\n\t  -------");

    Print_Stack ( sPtr->next );

}

