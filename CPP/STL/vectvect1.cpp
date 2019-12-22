#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

bool search_val (vector<int>  &vct, int start, int end, int val, int &pos)
{ 
    bool ret = false;
    if ( start > end )
    {
        pos = start;
        return  false;
    }

    int mid = ( ( start + end ) / 2) ; 

    if (vct[mid] > val)
        ret = search_val (vct, start, mid-1, val, pos);
    else if (vct[mid] < val)
        ret = search_val (vct, mid+1, end, val, pos);
    else
    {
        pos = mid;
        ret = true;
    }

    return ret;
}

int main() 
{
    vector <int> vct;
    int nelem = 0, val = 0;
    int query = 0;

    cin >> nelem;

    for (int i = 0; i < nelem; i++)
    {
        cin >> val;
        vct.push_back(val);
    }

    cin >> query;
    
    for (int i = 0; i < query; i++)
    {
        cin >> val;
        int size = vct.size();    
        int pos = 1;
        if ( search_val (vct, 0, size-1, val, pos) )
            cout << "Yes " << pos << endl;
        else
            cout << "No " << pos << endl;
    }

    return 0;
}
