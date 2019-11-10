#include "iostream"


using namespace std;

class derived;
class base
{
    private:
	virtual void fun()
	{
	    cout<<"\nBase\n";
	}
	friend int main();
};

class derived:public base
{
    public:
	void fun1()
	{
	    cout<<"\nDerived\n";
	}
};

int main()
{

    cout<<" hello\n";
    base *b = new derived;
    b->fun();
    return 0;
}
