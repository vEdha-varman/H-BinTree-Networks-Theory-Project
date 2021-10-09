// Inside Router
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <queue>
// #include <bits/stdc++.h>

using namespace std;

int strCmp(string a, string b)
{
	int aa = a.size(), bb = b.size();
	int i;
	for (i = 0; i < aa && i < bb; i++)
	{
		if (a[i] != b[i])
			return (a[i] > b[i]) ? 1 : -1;
	}
	if (aa == bb)
		return 0;
	else
	{
		if (aa == i)
			return (b[i] == '1') ? 1 : -1;
		else
			return (a[i] == '1') ? 1 : -1;
	}
}

class PortRange
{
public:
	int start = -1;
	int end = -1;
};
class Ruleset
{
public:
	string src = "";
	string dst = "";
	PortRange srcprt, dstprt;
	int protocol = 0;
	Ruleset() {}
	Ruleset(string s, string d, int srcprt_start, int srcprt_end, int dstprt_start, int dstprt_end, int ptl)
	{
		if (srcprt_start > srcprt_end || dstprt_start > dstprt_end ||
			srcprt_start < 0 || dstprt_start < 0 ||
			srcprt_end > (2 * INT16_MAX + 1) || dstprt_end > (2 * INT16_MAX + 1))
			cout << "\n\nPort Range Err\n\n";

		// Assuming unique entries
		else
		{
			this->src = s;
			this->dst = d;
			this->srcprt = {srcprt_start, srcprt_end};
			this->dstprt = {dstprt_start, dstprt_end};
			this->protocol = ptl;
		}
	}
};

class BSTreeNode
{
public:
	string prefix;
	BSTreeNode *left = NULL;
	BSTreeNode *right = NULL;
	BSTreeNode *child = NULL;
	vector<int> rule_ptr;
	BSTreeNode(string pfx = "") { this->prefix = pfx; }
};

void printLevelOrder(BSTreeNode *root)
{
	if (root == NULL)
		return;

	queue<BSTreeNode *> q;
	q.push(root);
	cout << "\n\n";

	while (q.empty() == false)
	{
		BSTreeNode *node = q.front();
		if (node)
			cout << node->prefix << ",";
		// else cout << " ";
		q.pop();

		if (node->left != NULL)
			q.push(node->left);

		if (node->right != NULL)
			q.push(node->right);
	}
}

// class BSTree
// {
// public:
// 	BSTreeNode *root = NULL;
// 	BSTree(/* args */) {}
// };
BSTreeNode *InsertSrc(string src, BSTreeNode *groot)
{
	if (groot == NULL)
	{
		// cout << src<<",";
		return new BSTreeNode(src);
	}
	else if (strCmp(src, groot->prefix) == -1)
	{
		groot->left = InsertSrc(src, groot->left);
	}
	else if (strCmp(src, groot->prefix) == 1)
	{
		groot->right = InsertSrc(src, groot->right);
	}
	else if (strCmp(src, groot->prefix) == 0)
	{
		// cout << groot->prefix << ":" << src << "\n\nSource Node already exists\n\n";
		// InsertDst(dst, groot->child);
	}
	else
	{
		cout << src << ":" << groot->prefix;
	}

	return groot;
}
BSTreeNode *SearchSrc(string src, BSTreeNode *groot)
{
	if (groot == NULL)
	{
		return NULL;
	}
	else if (strCmp(src, groot->prefix) == -1)
	{
		if(groot->left)
			return SearchSrc(src, groot->left);
		else return groot;
	}
	else if (strCmp(src, groot->prefix) == 1)
	{
		if(groot->right)
			return SearchSrc(src, groot->right);
		else return groot;
	}
	return groot;
}
BSTreeNode *InsertDst(string dst, BSTreeNode *groot, int rptr)
{
	if (groot == NULL)
	{
		return new BSTreeNode(dst);
	}
	else if (strCmp(dst, groot->prefix) == -1)
	{
		groot->left = InsertDst(dst, groot->left, rptr);
	}
	else if (strCmp(dst, groot->prefix) == 1)
	{
		groot->right = InsertDst(dst, groot->right, rptr);
	}
	else if (strCmp(dst, groot->prefix) == 0)
	{
		// cout << dst << ":" << groot->prefix << "\nDestn already exists\n\n";
		groot->rule_ptr.push_back(rptr);
	}
	return groot;
}
BSTreeNode *SearchDst(string dst, BSTreeNode *groot)
{
	if (groot == NULL)
	{
		return NULL;
	}
	else if (strCmp(dst, groot->prefix) == -1)
	{
		if(groot->left)
			return SearchDst(dst, groot->left);
		else return groot;
	}
	else if (strCmp(dst, groot->prefix) == 1)
	{
		if(groot->right)
			return SearchDst(dst, groot->right);
		else return groot;
	}
	return groot;
}
// class HBSTree
// {
// public:
// 	// BSTreeNode *root = NULL;
// 	HBSTree(/* args */)
// 	{
// 	}
// };

int main()
{
	// HBSTree hbst;
	BSTreeNode *root = NULL, *tmp = NULL;

	Ruleset rule_table[15];
	rule_table[0] = {"1000", "", 53, 53, 443, 443, 17};
	rule_table[1] = {"111", "101", 53, 53, 25, 25, 6};
	rule_table[2] = {"", "10", 53, 53, 25, 25, 17};
	rule_table[3] = {"101", "11", 67, 67, 5632, 5632, 6};
	rule_table[4] = {"01", "0011", 1024, 65535, 1024, 65535, 17};
	rule_table[5] = {"101", "11", 53, 53, 25, 25, 4};
	rule_table[6] = {"11", "0100", 0, 65535, 5632, 5632, 6};
	rule_table[7] = {"101", "1011", 0, 65535, 5632, 5632, 6};
	rule_table[8] = {"", "10", 53, 53, 25, 25, 6};
	rule_table[9] = {"11", "11", 0, 15576, 2783, 2783, 4};
	rule_table[10] = {"010", "00", 53, 53, 443, 443, 17};
	rule_table[11] = {"11", "00", 53, 53, 25, 25, 6};
	rule_table[12] = {"101", "0", 0, 65535, 5632, 5632, 6};
	rule_table[13] = {"01", "1", 53, 53, 443, 443, 17};
	rule_table[14] = {"01", "0", 0, 65535, 5632, 5632, 6};

	map<string, vector<int>> m;
	for (int i = 0; i < 15; i++)
	{
		m[rule_table[i].src].push_back(i);
	}

	// for (auto it : m)
	// {
	// 	cout << it.first << ":: ";
	// for(int itv : it.second)
	// {
	// 	cout<< itv << " ";
	// }cout << "\n";
	// }cout<<"\n\n\n";
	bool f = true;
	for (auto it : m)
	{
		if (f)
		{
			root = InsertSrc(it.first, root);
			f = false;
		}
		else
			InsertSrc(it.first, root);
	}
	for(auto it : m)
	{
		f = true;
		tmp = SearchSrc(it.first, root);
		for(int itv : it.second)
		{
			// cout << tmp->prefix <<"@"<< itv << " ";
			if(f)
			{
				tmp->child = InsertDst(rule_table[itv].dst, tmp->child, itv);
				f = false;
			}
			else
				InsertDst(rule_table[itv].dst, tmp->child, itv);
		}
	}
	// printLevelOrder(root);
 	cout << SearchDst("0011", SearchSrc("01", root))->rule_ptr[0];

	/**
	 * print the src prefixes in order
	 * then dest prefixes in order
	 * 
	 * then a search function, thats all
	 */

	cout << "\n\nUnder construction..\n\n"
		 << strCmp("010", "01");
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