#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"

struct StackNode
{
    int data;
    struct StackNode *next;
};

typedef struct StackNode Stack;

Stack * push ( Stack *root, int data );

int pop ( Stack ** root );

bool isEmpty (Stack * root );

void Print_Stack ( Stack * root );

Stack * Create_Stack ( int *array, int size );

