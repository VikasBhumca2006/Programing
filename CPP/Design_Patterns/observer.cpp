#include <iostream>
using namespace std;

class Subject
{
	vector < class Observer * > view;

    public:
    	attach ( Observer *obj )
	{
		view.push_back (obj );
	}

	notify()
	{
		for (int i = 0; i < view.size(); i++ )
		{
			view[i]->update();
		}
	}
	

};

