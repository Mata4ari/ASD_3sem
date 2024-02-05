#include <iostream>
#include <string>
using namespace std;

struct Item
{
	string name;
	int weight;
	int cost;
	Item() {}
	Item(string name,int weight,int cost)
	{
		this->name = name;
		this->weight = weight;
		this->cost = cost;
	}
};

struct Entry
{
	int cost=0;
	int freeWeight;
	string name="";
};


void main()
{
	int N;
	cin >> N;

	/*string str="";
	int c;
	int w;
	int K;
	cin >> K;
	Item* items = new Item[K];
	for (int i = 0; i < K; i++)
	{
		getline(cin, str);
		items[i].name = str;
		cin >> w;
		items[i].weight = w;
		cin >> c;
		items[i].cost = c;
	}*/

	int k = 4;
	Item* items = new Item[k]{ Item("zont",6,30),Item("stul",3,14),Item("stol",4,16),Item("gitara",2,9) };

	Entry** costs = new Entry*[k + 1];
	for (int i = 0; i < k + 1; i++)
	{
		costs[i] = new Entry[N + 1];
	}


	for (int i = 1; i < k + 1; i++)
	{
		for (int j = 0; j < N + 1; j++)
		{
			Item* max;
			if (costs[i-1][j].cost == 0)
			{
				if(items[i-1].weight<=j)
				{
					costs[i][j].cost = items[i - 1].cost;
					costs[i][j].freeWeight =j - items[i - 1].weight;
					costs[i][j].name = items[i - 1].name;
				}
			}
			else
			{
				Entry previous = costs[i - 1][j];
				if(items[i - 1].weight <= j)
				{
					int freeWeigth = j - items[i - 1].weight;
					if (items[i - 1].cost + costs[i - 1][freeWeigth].cost > previous.cost)
					{
						costs[i][j].cost = items[i - 1].cost + costs[i - 1][freeWeigth].cost;
						costs[i][j].freeWeight = freeWeigth- costs[i - 1][freeWeigth].freeWeight;
						costs[i][j].name = items[i - 1].name +"+"+ costs[i - 1][freeWeigth].name;
						continue;
					}
				}
				costs[i][j] = previous;
			}
		}
	}





	Entry max;
	for (int i = 1; i < k + 1; i++)
	{
		for (int j = 1; j < N + 1; j++)
		{
			if (max.cost < costs[i][j].cost)
				max = costs[i][j];
			cout << costs[i][j].cost << "\t";
		}
		cout << endl;
	}

	cout << max.cost << " " << max.name << endl;
	 
}