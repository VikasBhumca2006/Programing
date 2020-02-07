#include <iostream>
#include <memory>

using namespace std;
class Testshared
{
    public:
    
        Testshared()
        {  cout << "Created" << endl;   }        
        
        void show ()
        {  cout << "Testshared" << endl; }
        
        ~Testshared()
        {  cout << "Destroyed" << endl;   }
};

int main()
{
    shared_ptr <Testshared> ptr = make_shared<Testshared> ();
    cout << "Pointer ptr = " << ptr.get()<< endl;
    
    shared_ptr<Testshared> qtr (new Testshared);
    cout << "Pointer qtr = " << qtr.get()<< endl;
    
    shared_ptr <Testshared> obj = move(qtr);
    cout << "Pointer qtr = " << qtr.get()<< endl;
    cout << "Pointer obj = " << obj.get()<< endl;
    
    return 0;
}