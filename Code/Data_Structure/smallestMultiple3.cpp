#include<iostream>
#include<stdio.h>
#include<limits.h>
#include<stack>
#include<queue>
#include<list>
using namespace std; int max(int a, int b) { return a>b?a:b;} int Min(int a, int b) { return a<b?a:b;} 

int multiple1(int n)
{
  int c=1;
  int x=1;
  while(x%n!=0)
  {
    x=x*10+1;
    c++;
  }
  cout<<x<<endl;
}
int multiple(int n)
{
    int count=1,rem=1;
    while(rem)
    {
        rem = ( rem*10 + 1 ) % n;
        count++;
    }
    while(count--)
        printf("1");
    printf("\n");
}
int main(int argc, char **argv)
{
multiple(3);
multiple(13);
multiple(23);
multiple(33);
//multiple(53);

return 0;
}
