#include "iostream"
#include "stdio.h"
//#include < limits.h >
//#include < stack >
//#include < queue >
//#include < map >
#include <stdlib.h>

#define MAX 100

using namespace std;

class node
{
    public:
	node(int info,node* l, node*r)
	{
	    data = info;
	    left = l;
	    right = r;
	}

	node(int info)
	{
	    data = info;
	    left = NULL;right = NULL;
	}
	int data;
	node *left;
	node *right;	
};

class tree
{
    private:
	node *root;	
    public:
	tree(){ root = NULL ; }
	~tree(){};
	bool insert(int);
	void insertHelper(int info,node *tnode,node * newNode);
	void print();
	void printHelper(node* tnode,int &level,int &prevLevel);
	//	bool deleteNode();
	//	void printtree();
	//	bool search();
};

bool tree::insert(int data)
{
    node *newNode = new node(data);
    if(!newNode)
    {
	cout<<"memalloc failed";
	return false;
    }
    if(NULL == root)
    {
	cout<<"First entry";
	cout<<newNode->data;
	root = newNode;
	return true;		
    }
    node *tnode = root;
    insertHelper(data,tnode,newNode);
    return true;
}

void tree::insertHelper(int info,node *tnode,node * newNode)
{
    /*if(NULL == tnode)
      {
      cout<<"\ninserted\n";
      tnode=newNode;
      return;
      }*/
    if(info < tnode->data)
    {
	if(tnode->left == NULL)
	{
	    tnode->left = newNode;
	    return;	
	}	
	insertHelper(info,tnode->left,newNode);
    }
    if(info > tnode->data)
    {
	if(tnode->right == NULL)
	{
	    tnode->right = newNode;
	    return;	
	}	
	insertHelper(info,tnode->right,newNode);
    }	

}

void tree::print()
{
    if(NULL == root)
    {   
	cout<<"\nTree empty";
	return;
    }   

    node *tnode = root;
    int level = 0;
    int prevLevel = 0;
    cout<<"\n";
    printHelper(tnode,level,prevLevel);
}

void tree::printHelper(node* tnode,int &level,int &prevLevel)
{
    if(NULL != tnode->left)
    {   
	level = level+1;
	printHelper(tnode->left,level,prevLevel);
    }   
    if(NULL != tnode->right)
    {   
	level = level+1;
	printHelper(tnode->right,level,prevLevel);
    } 

    cout<<tnode->data;
    for(int i=0;i<=level;i++)
	cout<<"\t";
    if(prevLevel != level)
    {
	cout<<"\n";   	
	prevLevel = level;
    }

    return;
}

int main()
{
    tree t;
    t.insert(5);
    t.insert(4);
    t.insert(6);
    t.insert(3);
    t.print();
    return 1;

}
