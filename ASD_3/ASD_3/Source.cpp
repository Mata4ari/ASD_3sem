#include <iostream>
#include <utility>
#include <vector>
using namespace std;

struct Relation
{
	char node1;
	char node2;
	int cost;
	Relation(char a,char b, int n)
	{
		node1 = a;
		node2 = b;
		cost = n;
	}
};

void main()
{
	setlocale(LC_CTYPE, "ru");
	Relation pairs[24] = {{'A','B',7},{'A','C',10},{'B','A',7} ,{'B','F',9} ,{'B','G',27} ,{'C','A',10} ,{'C','F',8} ,{'C','E',31} ,{'D','E',32} 
	,{'D','H',17} ,{'D','I',21},{'E','C',31},{'E','D',32},{'F','C',8},{'F','B',9},{'F','H',11},{'G','B',27}
	,{'G','I',15} ,{'I','G',15} ,{'I','H',15},{'I','D',21},{'H','F',11},{'H','D',17},{'H','I',15} };

	vector<pair<char, int>> costs;
	
	cout << "Введите вершину графа" << endl;
	char a;
	cin >> a;

	costs.push_back(make_pair(a, 0));

	string str = "ABCDEFGIH";
	
		for (int j = 0; j < str.size(); j++)
		{
			if (str[j] != a)
			{
				costs.push_back(make_pair(str[j], INT_MAX));
			}
		}

	vector <char> chekedNodes;
	
	while (chekedNodes.size()!=costs.size())
	{
		pair<char, int> ch('z', INT_MAX);
		for (auto var : costs)
		{
			if (find(chekedNodes.begin(), chekedNodes.end(), var.first) != chekedNodes.end())
				continue;
			if ((ch.second) > var.second)
				ch = var;
		}
		
		for (auto var : pairs)
		{
			if (ch.first == var.node1)
			{
				for (auto &el : costs)
				{
					if (var.node2 == el.first && var.cost + ch.second < el.second)
					{
						el.second = var.cost + ch.second;
					}
				}
			}
		}
		chekedNodes.push_back(ch.first);
	}

	for (auto var : costs)
	{
		cout << var.first << " " << var.second << endl;
	}

}