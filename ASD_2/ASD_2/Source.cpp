#include <iostream>
#include <utility>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int N = 10;

void BFS(int n, vector<pair<int, int>>& v,bool* A)
{
	if (A[n - 1] == true)
		return;
	cout << n << endl;
	A[n - 1] = true;
	for (auto var : v)
	{
		if (var.first != n)
			continue;
		BFS(var.second, v, A);
	}
}

void BFS_mat(int n, bool** M, bool* A)
{
	if (A[n - 1] == true)
		return;
	cout << n << endl;
	A[n - 1] = true;
	for (int i = 0; i < N; i++)
	{
		if (M[n-1][i] == true)
		{
			BFS_mat(i+1, M, A);
		}
	}
}

void BFS_lst(int n, vector<int> *v, bool* A)
{
	if (A[n - 1] == true)
		return;
	cout << n << endl;
	A[n - 1] = true;
	for (int i = 0; i < v[n-1].size(); i++)
	{
		BFS_lst(v[n - 1][i]+1, v, A);
	}
}

void DFS(int n, bool** M, bool* A)
{

}

void main()
{
	vector<pair<int, int>> pairs;
	pairs.push_back(make_pair(1,2));
	pairs.push_back(make_pair(1,5));
	pairs.push_back(make_pair(2,1));
	pairs.push_back(make_pair(2,7));
	pairs.push_back(make_pair(2,8));
	pairs.push_back(make_pair(3,8));
	pairs.push_back(make_pair(4,6));
	pairs.push_back(make_pair(4,9));
	pairs.push_back(make_pair(5,1));
	pairs.push_back(make_pair(5,6));
	pairs.push_back(make_pair(6,4));
	pairs.push_back(make_pair(6,9));
	pairs.push_back(make_pair(7,2));
	pairs.push_back(make_pair(7,8));
	pairs.push_back(make_pair(8,2));
	pairs.push_back(make_pair(8,7));
	pairs.push_back(make_pair(8,3));
	pairs.push_back(make_pair(9,4));
	pairs.push_back(make_pair(9,6));
	pairs.push_back(make_pair(9,10));
	pairs.push_back(make_pair(10,9));

	bool* arr = new bool[N];
	for (int i = 0; i < N; i++)
		arr[i] = false;

	BFS(1, pairs,arr);
	for (int i = 0; i < N; i++)
		arr[i] = false;
	cout << "\n";


	bool** M = new bool*[N];
	for (int i = 0; i < N; i++)
	{
		M[i] = new bool[N];
	}

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			M[i][j] =false;
		}
	}

	for (auto var : pairs)
	{
		M[var.first-1][var.second-1] = true;
	}

	BFS_mat(1,M,arr);
	cout << "\n";

	for (int i = 0; i < N; i++)
		arr[i] = false;

	vector<int> vec[N];
	
	for (auto var : pairs)
	{
		vec[var.first-1].push_back(var.second-1);
	}

	BFS_lst(1, vec, arr);
	cout << "\n";
	
	for (int i = 0; i < N; i++)
		arr[i] = false;


	queue <int> que;
	vector <int> checkedNodes;

	que.push(1);

	while (!que.empty())
	{
		
		if(find(checkedNodes.begin(), checkedNodes.end(), que.front())==checkedNodes.end())
		{
			cout << que.front() << endl;;
			for (auto var : pairs)
			{
				if (var.first == que.front())
					que.push(var.second);
			}
		}
		checkedNodes.push_back(que.front());
		que.pop();
	}
	checkedNodes.clear();
	cout << "\n";


	que.push(1);

	while (!que.empty())
	{

		if (find(checkedNodes.begin(), checkedNodes.end(), que.front()) == checkedNodes.end())
		{
			cout << que.front() << endl;
			for (int i=0;i<N;i++)
			{
				if (M[que.front()-1][i] == true)
				{
					que.push(i + 1);
				}
			}
		}
		checkedNodes.push_back(que.front());
		que.pop();
	}
	checkedNodes.clear();
	cout << "\n";

	que.push(1);
	while (!que.empty())
	{
		if (find(checkedNodes.begin(), checkedNodes.end(), que.front()) == checkedNodes.end())
		{
			cout << que.front() << endl;;
			for (auto var : vec[que.front() - 1])
			{
					que.push(var+1);
			}
		}
		checkedNodes.push_back(que.front());
		que.pop();
	}

}