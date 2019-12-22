#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int main() 
{
    int rows = 0, query = 0;
    int i = 0, j = 0;
    int cols = 0, val;

    vector<vector<int> > mat;
    cin >> rows >> query;

    for (i = 0; i< rows; i++)
    {
        cin >> cols;
        vector<int> vct;

        for ( j = 0; j < cols; j++)
        {
            cin >> val; 
            vct.push_back(val); 
        }
        mat.push_back(vct);
    }

    cout << endl << endl << mat.size() << endl << endl << endl;
    
    for (i = 0; i< mat.size(); i++)
    {
        cout << "==" << mat[i].size() << __LINE__ << "==" << i << endl;
        for ( j = 0; j < mat[i].size(); j++)
        {
            cout << mat[i][j] << " "; 
        }
        cout <<endl;
    }

    return 0;
}
