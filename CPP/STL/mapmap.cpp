#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <set>
#include <map>
#include <algorithm>
using namespace std;


int main() 
{
    map<string, int> m;
    int query = 0;
    int type, val;
    string key;

    cin >> query;

    for (int i = 0; i < query; i++)
    {
        cin >> type ;
        switch ( type )
        {
            case 1:
            cin >> key >> val;
            cout << type << " " << key << " " << val <<endl;
            
            map<string,int>::iterator itr = m.find(key);
            
            //if ( itr != m.end() )
            {
              //  val = val + itr->second;
                //m.erase(key);    
            }
            m.insert(pair<string, int>(key, val) );
                break;

            case 2:
            cin >> key;
            cout << type << " " << key << endl;
            m.erase(key);
                break;

            case 3:
            cin >> key;
            cout << type << " " << key << endl;
            map<string, int>::iterator itr = m.find(key);
            if ( itr != m.end() )
                //cout << itr->second;
                break;
        }

    }

    return 0;
}
