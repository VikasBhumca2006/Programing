#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"

struct LinkListNode
{
    int data;
    struct LinkListNode *next;
    void *dataPtr;
};

typedef struct LinkListNode LinkList;

LinkList * addStart ( LinkList *root, int data );

LinkList * addLast ( LinkList *root, int data );

int removeStart ( LinkList ** root );

int removeLast ( LinkList ** root );

void Print_LinkList ( LinkList * root );

LinkList * Create_LinkList ( int *array, int size );

bool isEmpty (LinkList * root );

LinkList * Create_Node_DataPtr ( int dataPtr );

