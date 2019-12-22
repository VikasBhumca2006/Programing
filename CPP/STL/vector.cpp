#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main ()
{
    vector<string> vct;
    vector<string>::iterator itr;

    for ( int i =0; i <10; i++)
    {
        //string str1 = to_string(i);
        //string str2 = to_string(i);
        string str = "str1 + str2";
        vct.push_back(str);
    }

    for (itr = vct.begin(); itr != vct.end(); itr++ )
        cout << *itr << " " ;

    cout << endl;
    cout << "Size = " << vct.size() << endl;
    cout << "max_size = " << vct.max_size() << endl;
    cout << "capicity = " << vct.capacity() << endl;
    //cout << "shrink_to_fit = " << vct.shrink_to_fit() << endl;

    //cout << "pop_back = " << vct.pop_back() << endl;
    //cout << "pop_back = " << vct.pop_back() << endl;

    for (itr = vct.begin(); itr != vct.end(); itr++ )
        cout << *itr << " " ;


    return 0;
}

