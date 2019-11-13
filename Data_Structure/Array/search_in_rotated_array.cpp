#include <stdio.h>
#include <stdio.h>
//#include <stdlib.h>

/*
 * Search 8: In below Arrays  
 *
 *  4, 5, 6, 7, 8, 9, 1, 2, 3 => OutPut : index  4 
 *  5, 6, 7, 8, 9, 1, 2, 3, 4 => OutPut : index  3
 *  7, 8, 9, 1, 2, 3, 4, 5, 6 => OutPut : index  1
 *
 */

void print_arr ( int *arr, int size)
{
    printf ("\nStart : %s ", __func__);
    int idx = 0;
    printf ("\n");
    while ( idx < size )
    {
        printf ("  %d,  ",arr[idx++]);
    }
    printf ("\n");
    printf ("\nEnd : %s ", __func__);
}

int find_rotation_index ( int *arr, int startIndx, int endIndx )
{
    printf ("\nStart : %d === End : %d", arr[startIndx] , arr[endIndx]);
    int indx = -1;

    int mid = ( startIndx + endIndx ) / 2;

    if ( arr[startIndx] >  arr[mid] )
    {
        indx = find_rotation_index ( arr , startIndx, mid );
    }
    else if ( arr[startIndx] <  arr[mid] )
    {
        indx = find_rotation_index ( arr , mid, endIndx );
    }
    else
        indx =  mid;

    //printf ("Index = %d\n", indx);
    //printf ("\nEnd : %s ", __func__);
    return indx;

}

int binary_search ( int *arr, int startIndx, int endIndx , int element_val )
{
    //printf ("\nStart : %s ", __func__);
    int indx = -1;
    int mid = ( startIndx + endIndx ) / 2;

    if ( element_val >  arr[mid] )
    {
        indx = binary_search ( arr , mid , endIndx, element_val);
    }
    else if ( element_val <  arr[mid] )
    {
        indx = binary_search ( arr, startIndx, mid, element_val );
    }
    else if ( element_val ==  arr[mid] )
    {
        indx =  mid;
    }
    else
    {
        printf("Not found\n");
    }


    //printf ("Index = %d\n", indx);
    //printf ("\nEnd : %s ", __func__);
    return indx;

}

int search_element ( int *arr, int num_of_element, int element_val )
{
    printf ("\nStart : %s ", __func__);
    int ret_val = -1;

    int rotation_index = find_rotation_index ( arr, 0 , num_of_element );//, element_val );
    printf ("rotation_index = %d\n", rotation_index);

    if ( ( element_val > arr[0] ) && 
         ( element_val <  arr [ rotation_index ] ) )
    {
        ret_val = binary_search ( arr, 0, rotation_index, element_val );
    }
    else if ( (arr [ rotation_index + 1 ] < element_val ) &&
            ( arr [ num_of_element ] > element_val ) )
    {
        ret_val = binary_search ( arr, rotation_index + 1, num_of_element, element_val );
    }
    else if (  element_val == arr [ rotation_index ] )
    {
        return rotation_index;
    }
    printf ("\nEnd : %s ", __func__);
    return ret_val;
}

void rotate_array ( int *arr, int size, int rotateBy)
{
    printf ("\nStart : %s ", __func__);
    int idx , tmp;
    for ( idx = 0; rotateBy < size; idx++)// , rotateBy++);
    {
        tmp = arr [idx];
        arr [idx] = arr [ rotateBy ];//% size ];
        arr [ rotateBy++ ] = tmp;
    }
    printf ("\nEnd : %s ", __func__);
}

int main( )
{
    int arr[] = {1,2,3,4,5,6,7,8,9};

    print_arr ( arr, 9 );

    rotate_array ( arr , 9, 3 );
    print_arr ( arr, 9 );

    search_element ( arr, 9, 8);
    print_arr ( arr, 9 );

}

