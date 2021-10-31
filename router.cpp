// Inside Router
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <queue>
#include <chrono>
#include <windows.h>
// #include <bits/stdc++.h>

using namespace std;
using namespace std::chrono;

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
	BSTreeNode(string pfx = "", vector<int> rptr = {})
	{
		this->prefix = pfx;
		rule_ptr = rptr;
	}
};

class TrieNode
{
public:
	string prefix;
	TrieNode *left = NULL;
	TrieNode *right = NULL;
	TrieNode *child = NULL;
	bool isValid = false;
	vector<int> rule_ptr;
	TrieNode(string pfx = "", vector<int> rptr = {}, bool valid = false)
	{
		this->prefix = pfx;
		rule_ptr = rptr;
		isValid = valid;
	}
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
/**
// class BSTree
// {
// public:
// 	BSTreeNode *root = NULL;
// 	BSTree(/* args * /) {}
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
*/
int LinearSearch(Ruleset rules[], string src, string dst) {
	for (int i = 0; i < 15; i++)
	{
		Sleep(1);
		if (src == rules[i].src && dst == rules[i].dst)
		{
			return i;
		}
	}
	return -1;
}

BSTreeNode *SearchSrc(string src, BSTreeNode *groot)
{
	Sleep(1);
	if (groot == NULL)
	{
		return NULL;
	}
	else if (strCmp(src, groot->prefix) == -1)
	{
		if (groot->left)
			return SearchSrc(src, groot->left);
		else
			return groot;
	}
	else if (strCmp(src, groot->prefix) == 1)
	{
		if (groot->right)
			return SearchSrc(src, groot->right);
		else
			return groot;
	}
	return groot;
}
TrieNode *HTrie_SearchSrc(string src, TrieNode *groot, int i=0, TrieNode *bestMatch=NULL)
{
	Sleep(1);
	if (groot == NULL)
	{
		return NULL;
	}
	else if (src[i] == '0')
	{
		if(groot->isValid) bestMatch = groot;
		if (groot->left)
			return HTrie_SearchSrc(src, groot->left, i+1, bestMatch);
		else
			return bestMatch;
	}
	else if (src[i] == '1')
	{
		if(groot->isValid) bestMatch = groot;
		if (groot->right)
			return HTrie_SearchSrc(src, groot->right, i+1, bestMatch);
		else
			return bestMatch;
	}
	return groot;
}
/**
BSTreeNode *InsertDst(string dst, BSTreeNode *groot, int rptr)
{
	if (groot == NULL)
	{
		// cout << src<<",";
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
		// cout << groot->prefix << ":" << src << "\n\nDest Node already exists\n\n";
		groot->rule_ptr.push_back(rptr);
	}
	else
	{
		cout << dst << ":" << groot->prefix;
	}

	return groot;
}
*/
BSTreeNode *SearchDst(string dst, BSTreeNode *groot)
{
	Sleep(1);
	if (groot == NULL)
	{
		return NULL;
	}
	else if (strCmp(dst, groot->prefix) == -1)
	{
		if (groot->left)
			return SearchDst(dst, groot->left);
		else
			return groot;
	}
	else if (strCmp(dst, groot->prefix) == 1)
	{
		if (groot->right)
			return SearchDst(dst, groot->right);
		else
			return groot;
	}
	return groot;
}
TrieNode *HTrie_SearchDst(string dst, TrieNode *groot, int i=0, TrieNode *bestMatch=NULL)
{
	Sleep(1);
	if (groot == NULL)
	{
		return NULL;
	}
	else if (dst[i] == '0')
	{
		if(groot->isValid) bestMatch = groot;
		if (groot->left)
			return HTrie_SearchDst(dst, groot->left, i+1, bestMatch);
		else
			return bestMatch;
	}
	else if (dst[i] == '1')
	{
		if(groot->isValid) bestMatch = groot;
		if (groot->right)
			return HTrie_SearchDst(dst, groot->right, i+1, bestMatch);
		else
			return bestMatch;
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

TrieNode* HTrie_Builder(TrieNode *groot, Ruleset rt[])
{
	groot->left = new TrieNode("0");
	groot->right = new TrieNode("1");
	groot->left->right = new TrieNode("01",{},true);
	groot->left->right->left = new TrieNode("010",{},true);
	groot->right->right = new TrieNode("11",{},true);
	groot->right->right->right = new TrieNode("111",{},true);
	groot->right->left = new TrieNode("10");
	groot->right->left->right = new TrieNode("101",{},true);
	groot->right->left->left = new TrieNode("100");
	groot->right->left->left->left = new TrieNode("1000",{},true);

	groot->child = new TrieNode("");
	groot->child->right = new TrieNode("1");
	groot->child->right->left = new TrieNode("0",{2,8},true);
	groot->left->right->child = new TrieNode("");
	groot->left->right->child->right = new TrieNode("1",{13},true);
	groot->left->right->child->left = new TrieNode("0",{14},true);
	groot->left->right->child->left->left = new TrieNode("00");
	groot->left->right->child->left->left->right = new TrieNode("001");
	groot->left->right->child->left->left->right->right = new TrieNode("0011",{4},true);
	groot->left->right->left->child = new TrieNode("");
	groot->left->right->left->child->left = new TrieNode("0");
	groot->left->right->left->child->left->left = new TrieNode("00",{10},true);
	groot->right->right->right->child = new TrieNode("");
	groot->right->right->right->child->right = new TrieNode("1");
	groot->right->right->right->child->right->left = new TrieNode("10");
	groot->right->right->right->child->right->left->right = new TrieNode("101",{1},true);
	groot->right->left->left->left->child = new TrieNode("",{0},true);
	groot->right->left->right->child = new TrieNode("");
	groot->right->left->right->child->left = new TrieNode("0",{12},true);
	groot->right->left->right->child->right = new TrieNode("1");
	groot->right->left->right->child->right->right = new TrieNode("11",{3,5},true);
	groot->right->left->right->child->right->left = new TrieNode("10");
	groot->right->left->right->child->right->left->right = new TrieNode("101");
	groot->right->left->right->child->right->left->right->right = new TrieNode("1011",{7},true);
	groot->right->right->child = new TrieNode("");
	groot->right->right->child->right = new TrieNode("1");
	groot->right->right->child->right->right = new TrieNode("11",{9},true);
	groot->right->right->child->left = new TrieNode("0");
	groot->right->right->child->left->left = new TrieNode("00",{11},true);
	groot->right->right->child->left->right = new TrieNode("01");
	groot->right->right->child->left->right->left = new TrieNode("010");
	groot->right->right->child->left->right->left->left = new TrieNode("0100",{6},true);

	return groot;
}

BSTreeNode* Builder(BSTreeNode *groot, Ruleset rt[])
{
	// if(groot == NULL) return new BSTreeNode("");
	groot->left = new BSTreeNode("01");
	groot->left->left = new BSTreeNode("010");
	groot->right = new BSTreeNode("101");
	groot->right->left = new BSTreeNode("1000");
	groot->right->right = new BSTreeNode("11");
	groot->right->right->right = new BSTreeNode("111");

	groot->child = new BSTreeNode("10",{2,8});
	groot->left->child = new BSTreeNode("0",{14});
	groot->left->child->left = new BSTreeNode("0011",{4});
	groot->left->child->right = new BSTreeNode("1",{13});
	groot->left->left->child = new BSTreeNode("00", {10});
	groot->right->child = new BSTreeNode("1011",{7});
	groot->right->child->left = new BSTreeNode("0",{12});
	groot->right->child->right = new BSTreeNode("11",{3,5});
	groot->right->left->child = new BSTreeNode("", {0});
	groot->right->right->child = new BSTreeNode("0100",{6});
	groot->right->right->child->left = new BSTreeNode("00",{11});
	groot->right->right->child->right = new BSTreeNode("11",{9});
	groot->right->right->right->child = new BSTreeNode("101",{1});

	return groot;
}

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

	/**
	map<string, vector<int>> m;
	for (int i = 0; i < 15; i++)
	{
		m[rule_table[i].src].push_back(i);
	}
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
	for (int i = 0; i < 15; i++)
	{
		// f = true;
		tmp = SearchSrc(rule_table[i].src, root);
		if (tmp->child == NULL)
		{
			tmp->child = InsertDst(rule_table[i].dst, tmp->child, i);
			// f = false;
		}
		else
			InsertDst(rule_table[i].dst, tmp->child, i);
	}
	*/
	root = new BSTreeNode("");
	Builder(root, rule_table);
	// printLevelOrder(root);
	TrieNode *troot = new TrieNode("",{},true);
	HTrie_Builder(troot, rule_table);


	Ruleset pckt = {"0110", "0011", 1025, 1025, 1026, 1026, 6};
	BSTreeNode *temp;
	TrieNode *tempht;
	auto start = high_resolution_clock::now();
	int templs;
	for(int i=0; i<2; i++)
	{
		// temp = SearchDst(pckt.dst, SearchSrc(pckt.src, root)->child);
		// tempht = HTrie_SearchDst(pckt.dst, HTrie_SearchSrc(pckt.src,troot)->child);
		templs = LinearSearch(rule_table, pckt.src, pckt.dst);
	}
	auto stop = high_resolution_clock::now();

	cout << "\n\nRule followed:: "<<templs;//<<temp->rule_ptr[0];
	auto duration = duration_cast<microseconds>(stop - start);
	cout << "\nTime taken(micros):: "<< duration.count();
	// if(temp)
	// {
	// 	if(rule_table[ temp->rule_ptr[0]].protocol == pckt.protocol)
	// 		cout <<temp->rule_ptr[0];//<<" "<<strCmp("011","01");
	// 	else
	// 		cout << temp->rule_ptr[1];
	// }
	
	return 0;
}
