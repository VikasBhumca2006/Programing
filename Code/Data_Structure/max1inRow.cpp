#include<iostream>
#include<stdio.h>
#include<limits.h>
#include<stack>
#include<queue>
#include<list>
using namespace std; int max(int a, int b) { return a>b?a:b;} int Min(int a, int b) { return a<b?a:b;} 
#define R 4
#define C 4
int rowWithMax1s(bool m[R][C])
{
  int j=C-1;
  int i=0;
  int k=-1;
  while(j>=0 &&i<R)
  {
    if(m[i][j]==1) k=i;
  
    while(j>=0 && m[i][j] == 1) j--;
    if(j<0) return i;
    i++;
  }
  return k+1;
}

/* Driver program to test above functions */
int main()
{
    bool mat[R][C] = { {0, 0, 0, 1},
        {0, 0, 1, 1},
        {1, 1, 1, 1},
        {1, 1, 1, 1}
    };
 
    printf("Index of row with maximum 1s is %d \n", rowWithMax1s(mat));
 
    return 0;
}
