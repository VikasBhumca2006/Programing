#include<iostream>
#include<stdio.h>
#include<limits.h>
#include<stack>
#include<queue>
#include<list>
using namespace std; int max(int a, int b) { return a>b?a:b;} int Min(int a, int b) { return a<b?a:b;} 
int c=0;

int sum(int a, int b)
{
	c++;
	cout<<"Hi"<<endl;
	return a+b;
}

int util(int a, int b)
{
	if(b==1) return a;
	return sum(a,util(a,b-1));
}

int mul(int a, int b)
{
	int f=0;

	if(a==0 || b==0) 
		return 0;

	if(a<0) 
	{ 
		f=!f; 
		a=-a;
	}

	if(b<0) 
	{ 
		f=!f;
		b=-b;
	}

	int r=0;

	if(a<b) 
		r= util(b,a);

	r = util(a,b);

	if(f) 
		return -r;

	return r;
}

int main(int argc, char **argv)
{
	cout<<c;
	cout<<mul(3,2);
	return 0;
}
