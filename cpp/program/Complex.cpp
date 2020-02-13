#include <iostream>
using namespace std;
 
class complex
{
    private:
        int real;
        int imag;
    public:
        complex(int r = 0, int i = 0):real(r),imag(i){}
        friend ostream & operator << (ostream &out, const complex &c);
        
        void print() 
        { 
            cout << " " <<real <<" + " << imag <<"i"<<endl;  
        }
        
        complex operator* (const complex &c1)
        {
            complex c;
            real = real * c1.real + imag * c1.imag;
            imag = imag * c1.real + real * c1.imag;
            return *this;
        }
        
        complex operator+ (const complex &c1)
        {
            complex c;
            c.real = real + c1.real ;
            c.imag = imag * c1.imag;
            return c;
        }

        complex operator++ ()
        {
            complex c;
            c.real = ++real ;
            c.imag = ++imag;
            return c;
        }
        
        complex operator++ (int)
        {
            complex c;
            c.real = real++ ;
            c.imag = imag++;
            return c;
        }
};

ostream & operator << (ostream &out, const complex &c) 
{
    out << " " <<c.real <<" + " << c.imag <<" i"<<endl; 
    return out; 
} 
int main()
{
    complex c1(1,2);
    complex c2(3,4);
    complex c;
    cout << ++c1;
    cout << c2++;
    cout << c2;
   
    c = c1 + c2;
    c.print();
    c1.print();
    c2.print();
    
    c = c1 * c2;
    c.print();
    c1.print();
    c2.print();
   
    return 0;
}


