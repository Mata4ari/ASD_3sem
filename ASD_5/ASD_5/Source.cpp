#include <iostream>
#include <stack>
#include <vector>
using namespace std;

struct Relation
{
	int first;
	int second;
	int cost;
	int ind = -1;
};

void Prima(const int &N,int A[8][8])
{
	int si, sj;
	int min = INT_MAX;
	vector<int> cheaked;
	vector<pair<int,int>> pairs;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (A[i][j] != 0 && A[i][j] < min)
			{
				min = A[i][j];
				si = i;
				sj = j;
			}
		}
	}
	cheaked.push_back(si);
	cheaked.push_back(sj);
	pairs.push_back(make_pair(si, sj));

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (i==si||i==sj)
			{
				A[i][j] = 0;
			}
		}
	}
	int si1;
	int sj1;
	while (cheaked.size() != N)
	{
		min = INT_MAX;
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				if (find(cheaked.begin(), cheaked.end(),j)!=cheaked.end())
				{
					if(A[i][j]!=0&&A[i][j]<min)
					{
						min = A[i][j];
						si1 = i;
						sj1 = j;
					}
				}
			}
		}
		cheaked.push_back(si1);
		pairs.push_back(make_pair(si1, sj1));

		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				if (i == si1)
				{
					A[i][j] = 0;
				}
			}
		}
	}

	
	for (auto i : pairs)
	{
		cout << i.first + 1 << "  " << i.second + 1 << endl;
	}
}

void Krascala(const int N, int A[8][8])
{
	int M[8][8] = { {0},{1},{2},{3},{4},{5},{6},{7} };

	vector<Relation> relations;
	
	vector<int> cheaked;



	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (find(cheaked.begin(), cheaked.end(), j) == cheaked.end())
			{
				if (A[i][j] != 0)
				{
					Relation *rel = new (Relation);
					rel->first = i;
					rel->second = j;
					rel->cost = A[i][j];
					cheaked.push_back(i);
					relations.push_back(*rel);
				}
			}
		}
	}


	for (int i = 0; i < relations.size(); i++)
	{
		for (int j = i; j < relations.size(); j++)
		{
			if (relations[i].cost > relations[j].cost)
			{
				swap(relations[i], relations[j]);
			}
		}
	}

	vector<Relation> B;
	vector <vector<int>> nodes;
	for (int i = 0; i < N; i++)
	{
		vector<int> v;
		v.push_back(i);
		nodes.push_back(v);
	}

	for (auto var : relations)
	{
		for (auto &i : nodes)
		{
			if (find(i.begin(), i.end(), var.first) != i.end())
			{
				for (auto &j : nodes)
				{
					if (find(j.begin(), j.end(), var.second) != j.end())
					{
						if (i.size() == 1 && j.size() == 1)
						{
							i.push_back(var.second);
							j.clear();
							B.push_back(var);
							goto exit;
						}
						if ((i.size() > 1 && j.size() == 1)|| (i.size() == 1 && j.size() > 1))
						{
							if (i.size() > 1 && j.size() == 1)
							{
								i.push_back(var.second);
								j.clear();
								B.push_back(var);
							}
							else
							{
								j.push_back(var.first);
								i.clear();
								B.push_back(var);
							}
							goto exit;
						}
						if (i.size()>1&&j.size()>1)
						{
							if (i != j)
							{
								for (auto it : j)
									i.push_back(it);
								j.clear();
								B.push_back(var);
							}
							goto exit;
						}
					}
				}
			}
		}
	exit: ;
	}


	for (auto var : B)
	{
		cout <<var.first+1<<" "<<var.second+1<<"   " << var.cost << endl;
	}
}

void main()
{
	const int N = 8;
	int A[N][N] = {
		{0,2,0,8,2,0,0,0},
		{2,0,3,10,5,0,0,0},
		{0,3,0,0,12,0,0,7},
		{8,10,0,0,14,3,1,0},
		{2,5,12,14,0,11,4,8},
		{0,0,0,3,11,0,6,0},
		{0,0,0,1,4,6,0,9},
		{0,0,7,0,8,0,9,0}};

	
	
	Krascala(N, A);
	cout << endl << endl;
	Prima(N, A);
}