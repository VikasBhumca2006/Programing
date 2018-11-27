#include<iostream>
#include<stdio.h>
#include<limits.h>
#include<stack>
#include<queue>
#include<list>
using namespace std; int max(int a, int b) { return a>b?a:b;} int Min(int a, int b) { return a<b?a:b;} 

bool balance(char* p)
{
  stack <char> s;
  int i = 0 ;
  while(p[i]!='\0')
  {
    if(p[i]=='{' || p[i] == '(' || p[i]=='[' )
      s.push(p[i]);

    if( (p[i]== '}' ||p[i]== ')' ||p[i]== ']' ))
    {
      if(p[i]=='}' && s.top()!= '{') return false;
      if(p[i]==')' && s.top()!= '(') return false;
      if(p[i]==']' && s.top()!= '[') return false;
     s.pop(); 
    }
    i++;
  }
  if(s.empty()) return true;
  return false;
}
int main(int argc, char **argv)
{
  char a[] = "[(5+4}*{(5/7)-(5+(8/4))}]";
  cout<<balance(a);

  return 0;
}
