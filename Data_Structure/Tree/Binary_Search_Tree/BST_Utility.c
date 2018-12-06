#include "stdio.h"
#include "stdlib.h"
#include "BST_Utility.h"
#include "../../../OS/Memory/Memory_Manager.h"
#include "../../../Logger/Logger_Utility.h"

int getMax ( int x, int y)
{
    return ( x > y ? x : y );
}

int power ( int x, int y )
{
    int result = 1, idx ;

    for ( idx = 0; idx < y; idx++ )
        result = result * x;

    return result;
}

int Height_Tree ( Tree * root )
{
    if ( NULL == root )
    {
        return 0;
    }

    return ( 1 + getMax ( Height_Tree(root->left) , Height_Tree(root->right) ) );
}


Tree * create_Node ( int data )
{
    //Tree * ptr = ( Tree * ) malloc (sizeof(Tree));
    Tree * ptr = ( Tree * ) alloc_mem (sizeof(Tree));
    if ( ptr )
    {
        ptr->left = NULL;
        ptr->right = NULL;
        ptr->data = data;
    }
    return ptr;
}

Tree * Insert_Node ( Tree *root, int data )
{
    if ( NULL == root )
    {
        return create_Node ( data );
    }

    if ( root->data < data )
    {
        root->right = Insert_Node ( root->right, data );
        return root;
    }

    if ( root->data > data )
    {
        root->left = Insert_Node ( root->left, data );
        return root;
    }

    printf ("Duplicate Number");
    return root;
}

Tree * Create_Tree ( int *array, int size )
{
    int idx = 0;
    Tree * root = NULL;
    printf ("\n In %s\n",__func__);

    for ( idx = 0; idx < size; idx++ )
    {
        root = Insert_Node ( root, array[idx] );
    }

    return root;

}

void InOrder_Recursive ( Tree * root )
{
    if ( NULL == root )
    {
        return;
    }
    InOrder_Recursive ( root->left );
    printf (" %d ", root->data );
    InOrder_Recursive ( root->right );
}

void print_Level ( Tree * root, int space, int level, int currLevel )
{
    int idx = 0;
    if ( level == currLevel )
    {
        for ( idx = 0; idx < space; idx++ )
            printf (" ");
        
        if ( NULL == root )
            printf ("  ");
        else
            if ( root->data > 9 )
                printf ("%d",root->data);
            else
                printf ("%d ",root->data);

        for ( idx = 0; idx < space; idx++ )
            printf (" ");
    }
    else
    {
        if ( !root->left )
            print_Level ( NULL, space, level, currLevel+1 );
        else
            print_Level ( root->left, space, level, currLevel+1 );

        if ( !root->right )
            print_Level ( NULL, space, level, currLevel+1 );
        else
            print_Level ( root->right, space, level, currLevel+1 );
    }
}

void Print_Tree ( Tree * root )
{
    printf ("\n In %s\n",__func__);
    int hight =  Height_Tree ( root );
    int idx = 0;

    int row = 2 * hight + 1;
    int column = power ( 2, hight + 1 ) - 1;

    printf ("\n ROW = [%d], COLUMN = [%d]\n\n", row, column );

    int space = column ;/// 2 ;
    int i;

    for ( i = 0; i < hight; i++ )
    {
        print_Level ( root, space, i+1, 1 );

        for ( idx = 0; idx < hight - i; idx++ )
            printf ("\n");

        space = space / 2;
    }
}



Tree * Delete_Node ( Tree *root, int data )
{
    Tree *tmp = NULL;
    if ( NULL == root )
    {
        return NULL;
    }

    if ( data < root->data )
    {
        root->left = Delete_Node ( root->left, data );
    }

    else if ( data > root->data )
    {
        root->right = Delete_Node ( root->right, data );
    }
    else
    {

        if ( NULL == root->left ) 
        {
            tmp = root->right;
            free_mem (root);
            return tmp;

        }

        if ( NULL == root->right ) 
        {
            tmp = root->left;
            free_mem (root);
            return tmp;
        }

        tmp = Min_Value_Node ( root->right );

        printf ("\n Min data = %d", tmp->data );

        root->data = tmp->data;

        root->right = Delete_Node ( root->right, tmp->data );
    }

    return root;
}

Tree * Min_Value_Node ( Tree * root )
{
    while ( root )
    {
        if ( NULL == root-> left )
            return root;
        root = root->left;
    }

    return NULL;
}


































