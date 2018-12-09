#include "LinkList_Utility.h"

LinkList * Create_LinkList ( int *array, int size )
{
    LinkList * listPtr = NULL;
    int idx = 0;

    for ( idx = 0; idx < size; idx++ )
    {
        listPtr = addStart ( listPtr, array[idx] );
    }

    return listPtr;
}

LinkList * Create_Node ( int data )
{
    LinkList * ptr = ( LinkList * ) malloc ( sizeof(LinkList) );
    if ( ptr )
    {
        ptr->data = data;
        ptr->next = NULL;
        ptr->dataPtr = NULL;
        return ptr;
    }
    return NULL;
}

LinkList * Create_Node_DataPtr ( int dataPtr )
{
    LinkList * ptr = ( LinkList * ) malloc ( sizeof(LinkList) );
    if ( ptr )
    {
        ptr->data = data;
        ptr->next = NULL;
        ptr->dataPtr = NULL;
        return ptr;
    }
    return NULL;
}


LinkList * addStart ( LinkList *listPtr, int data )
{
    LinkList * tmp = listPtr;
    listPtr = Create_Node ( data );
    listPtr->next = tmp;
    return listPtr;
}

int removeStart ( LinkList **listPtr )
{

    printf ("\n Pop ");

    if ( isEmpty (*listPtr) )
        return -1;

    LinkList * tmp = *listPtr;
    int data = tmp->data;

    *listPtr = tmp->next;
    free ( tmp );

    return data ;
}

bool isEmpty (LinkList * listPtr )
{
    return ( listPtr == NULL );
}

void Print_LinkList ( LinkList * listPtr )
{
    if ( NULL == listPtr )
        return;

    if ( listPtr->data > 9 )
        printf ( "\n\t |   %d  |", listPtr->data );
    else
        printf ( "\n\t |   %d   |", listPtr->data );

    printf ( "\n\t  -------");

    Print_LinkList ( listPtr->next );
}

