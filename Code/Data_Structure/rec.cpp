#include<iostream>
#include<stdio.h>
#include<limits.h>
#include<stack>
#include<queue>
#include<list>
using namespace std; int max(int a, int b) { return a>b?a:b;} int Min(int a, int b) { return a<b?a:b;} 

int main(int argc, char **argv)
{
union A{
long int y[5];
union B{
double g;
union C{
int k;
union D{
char ch;
int x[5];
}s;
}a;
}b;
}*p;
p = new A;//(union A*) malloc (sizeof(union A));
p->b.a.k=15;
printf(" %d %d \n",p->b.a.s.x[0],p->y[0]);
cout<<sizeof( long long int );
return 0;
}
void fun()
{
char c;
if((c=getchar())!='\n')
fun();
printf("%c",c);
}
