#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "../../OS/Memory/Memory_Manager.h"
#include "../../Logger/Logger_Utility.h"

struct QueueNode
{
    int data;
    struct QueueNode *next;
    void *dataPtr ;
};

typedef struct QueueNode Queue;

Queue * enqueue ( Queue *root, int data );

int dequeue ( Queue ** root );

void Print_Queue ( Queue * root );

Queue * Create_Queue ( int *array, int size );

bool isEmpty (Queue * root );

void * dequeue_DataPtr ( Queue **qPtr );

Queue * enqueue_DataPtr ( Queue *qPtr, int dataPtr );

Queue * Create_Node_DataPtr ( int dataPtr );

