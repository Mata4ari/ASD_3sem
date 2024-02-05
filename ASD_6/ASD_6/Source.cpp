#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

struct node
{
	char ch;
	string name;
	int col;
	bool IsLeaf=0;
	node* left=nullptr;
	node* right=nullptr;
	static node* root;
};

bool compar( node*left,  node* right)
{
	return left->col > right->col;
}

void LRK(node*p,string str)
{
	if (p->IsLeaf)
	{
		cout << p->ch << " " << str<<endl;
		return;
	}
	if (p->left != nullptr)
		LRK(p->left, str + "0");
	if (p->right != nullptr)
		LRK(p->right, str + "1");
}

string findCode(char ch, string str,node*root)
{
	node* p=root;
	while(true)
	{
		if (p->IsLeaf)
		{
			return str;
		}
		if(p->left != nullptr)
		{
			if (find(p->left->name.begin(), p->left->name.end(), ch) != p->left->name.end())
			{
				str += "0";
				p = p->left;
			}
		}
		if(p->right != nullptr)
		{
			if (find(p->right->name.begin(), p->right->name.end(), ch) != p->right->name.end())
			{
				str += "1";
				p = p->right;
			}
		}
	}
}

void main()
{
	string str;
	getline(cin, str);

	vector<node*> nodes;
	for (int i = 0; i < str.size(); i++)
	{
		bool x = 0;
		for (auto& var : nodes)
		{
			if (str[i] == var->ch)
			{
				var->col++;
				x = 1;
				break;
			}
		}
		if (!x)
		{
			node* p = new node;
			p->ch = str[i];
			p->name += str[i];
			p->col = 1;
			p->IsLeaf = 1;
			nodes.push_back(p);
		}
	}

	sort(nodes.begin(), nodes.end(), compar);
	for (auto i : nodes)
	{
		cout << i->ch << " " << i->col << endl;
	}
	cout << endl << endl;


	while (nodes.size() != 1)
	{
		node* p = new node;
		p->right = nodes[nodes.size()-1];
		p->left = nodes[nodes.size() - 2];
		p->col = p->right->col + p->left->col;
		p->name += p->right->name + p->left->name;
		nodes.pop_back(); nodes.pop_back();
		nodes.push_back(p);
		sort(nodes.begin(), nodes.end(), compar);
	}
	LRK(nodes[0], "");


	cout << endl << endl; 
	for (auto i : str)
	{
		cout << findCode(i, "", nodes[0]);
	}

}