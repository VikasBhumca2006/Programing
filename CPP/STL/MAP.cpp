#include "iostream"
#include "iterator"
#include "map"

using namespace std;

int main()
{
	map<int, char *> ageName;

	ageName.insert ( pair <int, char *> (1, "Abcdef" ) );
	ageName.insert ( pair <int, char *> (3, "Bcdefg" ) );
	ageName.insert ( pair <int, char *> (2, "Cdefgh" ) );
	ageName.insert ( pair <int, char *> (4, "Defghi" ) );
    ageName[10] = "Efghij";

	map <int, char *>::iterator it;

	for ( it = ageName.begin(); it != ageName.end(); it++ )
	{
		cout << "    " << it->first << "   " << it->second << endl;
	}
	
	map<char*, int> nameAge;

	nameAge.insert ( pair <char *, int> ("Abcdef", 1 ));
	nameAge.insert ( pair <char *, int> ("2", 9 ));

	for ( map<char*, int>::iterator it2 = nameAge.begin(); it2 != nameAge.end(); it2++ )
	{
		cout << "    " << it2->first << "   " << it2->second << endl;
	}
    map<char*, int>::iterator findItr = nameAge.find ("Abcdef");

    if ( findItr != nameAge.end() )
        cout << "find (Abcdef) = " << findItr->first << " , " << findItr->second << endl;
    else
        cout << "Not found" ;
            

//    cout << "find (bcdef) = " << nameAge.find ("bcdef") << endl;

    return 0;
}

