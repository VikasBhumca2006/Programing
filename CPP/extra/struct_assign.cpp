#include <iostream>
using namespace std;

struct timeval {
	long tv_sec;
	long tv_usec;
};

int main()
{
	struct timeval tm = {0};
	cout << tm.tv_sec ;
	cout << tm.tv_usec ;
	tm.tv_sec = 10;
	tm.tv_usec = 20;
	cout << tm.tv_sec ;
	cout << tm.tv_usec ;
	tm = 0;
	cout << tm.tv_sec ;
	cout << tm.tv_usec ;

    
   return 0;
}
