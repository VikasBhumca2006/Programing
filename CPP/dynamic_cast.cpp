#include <iostream>
#include "stdlib.h"

using namespace std;


class B
{
    public:

        B(){}
        virtual ~B(){}
};

//class D1 : private B
class D1 : public B
{
    public:
        D1(){}
        ~D1(){}
};
#if 0
class D2 : B
{
    public:
        D2(){}
        ~D2(){}
};
#endif
#if 1
int main()
{
    B *bPtr = NULL;
    D1 *d1Ptr = new D1();

    bPtr = dynamic_cast<B *> (d1Ptr);

    if ( bPtr == NULL )
    {
        cout << "bPtr = dynamic_cast<B*> d1Ptr;" << endl;
    }

}
#endif
