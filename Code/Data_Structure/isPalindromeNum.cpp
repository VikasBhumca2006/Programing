#include<iostream>
#include<stdio.h>
#include<limits.h>
#include<stack>
#include<queue>
#include<list>
using namespace std; int max(int a, int b) { return a>b?a:b;} int Min(int a, int b) { return a<b?a:b;} 

bool isPalindrome(int n)
{
int r =0;
if(n<0) n=-n;
int l=n;
while(l) { r=r*10 +l%10;  l = l/10;}
while(r&n)
{
if(r%10!=n%10) return false;
r=r/10;n=n/10;
}
if(r||n) return false;
return true;

}
int main(int argc, char **argv)
{
cout<<isPalindrome(1122);

return 0;
}
