#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"

struct QueueNode
{
    int data;
    struct QueueNode *next;
};

typedef struct QueueNode Queue;

Queue * enqueue ( Queue *root, int data );

int dequeue ( Queue ** root );

void Print_Queue ( Queue * root );

Queue * Create_Queue ( int *array, int size );

bool isEmpty (Queue * root );

