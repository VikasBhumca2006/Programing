#include <iostream>
using namespace std;

class A 
{
public:
void display(){ cout << "IN A" << endl; }
virtual ~A(){}; 
};

class B : virtual private A
{ 
};

class C : virtual public A
{ 
};

class D : public B, public C {};

int main()
{
   //A *a = dynamic_cast<A*>(new B());
   //if(!a)
   //   cout << "B to A is bad cast" << endl;

   //A *a 
   B *b = new D();
   D *d = dynamic_cast<D*>(b);
   if(d)
   {
      cout << "Down casted B to D" << endl;
      C *c = dynamic_cast<C*>(d);
      if(c)
      {
        cout << "UP casted D to C" << endl;
   	A *a = dynamic_cast<A*>(c);
   	if(a)
	{
      	    cout << "UP casted C to A" << endl;
            a->display();
	}
   	else
            cout << "bad cast C -> A" << endl;
      }
      else
         cout << "bad cast D -> C" << endl;
   }
   else
      cout << "bad cast B -> D" << endl;


    
   return 0;
}
