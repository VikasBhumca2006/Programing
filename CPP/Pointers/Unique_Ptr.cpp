#include <iostream>
#include <memory>

using namespace std;
class TestUnique
{
    public:
    
        TestUnique()
        {  cout << "Created" << endl;   }        
        
        void show ()
        {  cout << "TestUnique" << endl; }
        
        ~TestUnique()
        {  cout << "Destroyed" << endl;   }
        
        void del () { cout << "Delete " ; }
};

int main()
{
    unique_ptr<TestUnique[]> arr = make_unique<TestUnique[]>(2);

    unique_ptr <TestUnique> ptr = make_unique<TestUnique, del> ();
    cout << "Pointer ptr = " << ptr.get()<< endl;
    
    TestUnique *ctr = ptr.release();
    cout << "Release Pointer ptr = " << ptr.get()<< endl;
    cout << "Pointer ctr = " << ctr<< endl;
    
    unique_ptr<TestUnique> qtr (new TestUnique);
    cout << "Pointer qtr = " << qtr.get()<< endl;
    
    unique_ptr <TestUnique> obj = move(qtr);
    cout << "Pointer qtr = " << qtr.get()<< endl;
    cout << "Pointer obj = " << obj.get()<< endl;
    
    unique_ptr <TestUnique> abc (new TestUnique(), &del )
    
    return 0;
}


