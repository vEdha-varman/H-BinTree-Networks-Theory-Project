// Inside Router
#include <iostream>
#include <string>
// #include <bits/stdc++.h>

using namespace std;

bool strCmp(string a, string b)
{
	int aa = a.size(), bb = b.size();
	// if (aa != bb)
	// {
	// 	return aa > bb;
	// }
	// else
	{
		int i;
		for (i = 0; i < aa && i < bb; i++)
		{
			if (a[i] != b[i])
			{
				return a[i] > b[i];
			}
		}
		if (aa!=bb)
		{
			if (aa == i)
			{
				/* code */
			}
			
		}
		
	}
	
	
}

class BSTreeNode
{
public:
	string prefix;
	BSTreeNode *left;
	BSTreeNode *right;
	BSTreeNode *child;
	BSTreeNode(/* args */){}
};

class BSTree
{
public:
	BSTreeNode *root;
	BSTree(/* args */){}
};

class HBSTree
{
public:
	HBSTree(/* args */){}
};

int main()
{
	cout << "\n\nUnder construction..\n\n" << strCmp("1000", "101");
	return 0;
}






/**
 * first the strCmp() should be able to tell whether the first arg should be to left(0) or right(1) to the 2nd arg
 * 
 * then comes the tree alone
 * 
 * then the clients and servers with ip address kick in,
 * followed by port(/ranges)
 */