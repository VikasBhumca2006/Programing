#include<iostream>
#include<stdio.h>
#include<limits.h>
#include<stack>
#include<queue>
#include<algorithm>
using namespace std; int max(int a, int b) { return a>b?a:b;} int Min(int a, int b) { return a<b?a:b;} 

int comp(const void *a_,const  void*b_)
{
  int a= *(int*)a_;
  int b=*(int*)b_;
  return a>b;
}
bool isPairSum(int a[], int n, int s)
{
  qsort(a,n,sizeof(a[0]),comp);
  int l=0,h=n-1;
  while(l<h)
  {
    if(a[l]+a[h]==s) return true;
    else if( a[l]+a[h]<s) l++;
    else h--;
  }
  return false;
}
int main(int argc, char **argv)
{
  int a[]={18,21,11,28,31,38,40,55,60,62};
  cout<<isPairSum(a,sizeof(a)/sizeof(a[0]),66);
  return 0;
}
