/*
    Find element at given index after a number of Left Circular Rotations

    Ex : Find element at index 2 

        Array = 1, 2,  3,  4,  5,  6
        Rotation :  { 0, 3 }, { 2, 5 }

        Array after Left Circular Rotations {0, 3}
        2,  3,  4,  1,  5,  6

        Array after Left Circular Rotations {2, 5}
        2,  3,  1,  5,  6,  4
*/

#include <iostream>
using namespace std; 
#define ROTATIONS  2; 

// Function to compute the element at given index 
int findElement(int arr[], int ranges[][2], 
            int rotations, int index) 
{ 
    int i = 0;
    for ( i = rotations - 1; i >= 0; i-- )
    { 
        int left = ranges[i][0]; 
        int right = ranges[i][1]; 

        cout << " left = " << left << " right = "<< right ;

        if (left <= index && right >= index) 
        { 
            if (index == right) 
                index = left; 
            else
                index++ ;
        } 
        cout << " index = " << index << endl  ;
    } 

    return arr[index]; 
} 

// Driver 
int main() 
{ 
    //int arr[] = { 2,5,1,3,9,4,8,5,11,7,12 }; 
    //int ranges[ROTATIONS][2] = { { 0, 3 }, { 0, 5 }, {1,3} , {2,4},{1,9} }; 

    int arr[] = { 1, 2, 3, 4, 5, 6 }; 
    int ranges[2][2] = { { 0, 3 }, { 2, 5 } }; 


    int index = 2; 

    cout << findElement(arr, ranges, 2, index); 

    return 0; 

} 

