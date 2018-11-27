#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"

struct TreeNode
{
    int data;
    struct TreeNode *left; /* left child */
    struct TreeNode *right; /* right child */

    struct TreeNode *parent;
};

typedef struct TreeNode Tree;

Tree * Create_Node ( int data );

Tree * Insert_Node ( Tree *root, int data );

Tree * Create_Tree ( int *array, int size );

Tree * Delete_Node ( Tree *root, int data );

Tree * Min_Value_Node (Tree * root );

void Print_Tree ( Tree * root );

void InOrder_Recursive ( Tree * root );

void PreOrder_Recursive ( Tree * root );

void PostOrder_Recursive ( Tree * root );

