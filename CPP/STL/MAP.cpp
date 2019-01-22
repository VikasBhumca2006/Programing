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

	map <int, char *>::iterator it;

	for ( it = ageName.begin(); it != ageName.end(); it++ )
	{
		cout << "    " << it->first << "   " << it->second;
	}
	
	map<int, char *> nameAge;

	nameAge.insert ( pair <char *, int> ("Abcdef", 1 ));
	nameAge.insert ( pair <char *, int> (2, "Bcdefg" ));


}

