#include "stdio.h"
#include "stdlib.h"
#include "Tree_Utility.h"


Tree * create_Node ( int data )
{
    Tree * ptr = ( Tree * ) malloc (sizeof(Tree));
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

void Print_Tree ( Tree * root )
{
    printf ("\n In %s\n",__func__);

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
            free (root);
            return tmp;

        }

        if ( NULL == root->right ) 
        {
            tmp = root->left;
            free (root);
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


































