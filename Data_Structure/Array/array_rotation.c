#include <stdio.h>
#include <stdio.h>
//#include <stdlib.h>

/*
 * Array rotation
 *
 * Input  : 1, 2, 3, 4, 5, 6, 7, 8, 9
 *
 * OutPut : 4, 5, 6, 7, 8, 9, 1, 2, 3 => index for rotation 4
 * OutPut : 5, 6, 7, 8, 9, 1, 2, 3, 4 => index for rotation 5
 * OutPut : 7, 8, 9, 1, 2, 3, 4, 5, 6 => index for rotation 6
 *
 */

void print_arr ( int *arr, int size)
{
    int idx = 0;
    printf ("\n");
    while ( idx < size )
    {
        printf ("  %d,  ",arr[idx++]);
    }
    printf ("\n");
}


void rotate_array ( int *arr, int size, int rotateBy)
{
    //printf ("\nStart : Rotate Array ");
    int idx , tmp;
    for ( idx = 0; rotateBy <= size; idx++)// , rotateBy++);
    {
        //print_arr ( arr, 9 );
        tmp = arr [idx];
        arr [idx] = arr [ rotateBy ];//% size ];
        arr [ rotateBy++ ] = tmp;
    }
    //printf ("\nEnd  : Rotate Array ");
}

int main( )
{
    int arr[] = {1,2,3,4,5,6,7,8,9};

    print_arr ( arr, 9 );

    rotate_array ( arr , 9, 3 );
    print_arr ( arr, 9 );

}

