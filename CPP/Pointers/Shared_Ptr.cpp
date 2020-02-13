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

void Deleteor(Testshared *ptr)
{
    cout << "Deleteor" << endl;   
}

int main()
{
    shared_ptr <Testshared> ptr = make_shared<Testshared> ();
    cout << "Pointer ptr = " << ptr.get()<< endl;
    
    shared_ptr<Testshared> qtr (new Testshared);
    cout << "Pointer qtr = " << qtr.get()<< endl;
    
    shared_ptr <Testshared> obj = move(qtr);
    cout << "Pointer qtr = " << qtr.get()<< endl;
    cout << "Pointer obj = " << obj.get()<< endl;
    
    cout << "Created with deleteor" << endl;
    shared_ptr<Testshared> delPtr (new Testshared(), &Deleteor);
    
    return 0;
}



