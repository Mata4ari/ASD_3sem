#include <iostream>
#include <vector>
using namespace std;

void main()
{
	int n;
	cin >> n;
	int* A = new int[n];
	for (int i = 0; i < n; i++)
	{
		A[i] = rand() % 30;
	}

	for (int i = 0; i < n; i++)
	{
		cout << A[i] << "\t";
	}
	cout << endl;

	int* MaxSub=new int[n];
	int* Idx = new int[n];
	Idx[0] = -1;
	MaxSub[0]=1;


	for (int i = 1; i < n; i++)
	{
		bool x=1;
		int maxsub = -1;
		for (int j = 0; j < i; j++)
		{
			if (A[i] > A[j]&& maxsub< MaxSub[j] + 1)
			{
				maxsub= MaxSub[j] + 1;
				MaxSub[i] = MaxSub[j] + 1;
				Idx[i] = j;
				x = 0;
			}
		}
		if (x)
		{
			MaxSub[i]=1;
			Idx[i] = -1;
		}
	}


	/*for (int i = 0; i < n; i++)
	{
		cout << MaxSub[i] << "\t";
	}
	cout << endl;
	for (int i = 0; i < n; i++)
	{
		cout << Idx[i] << "\t";
	}
	cout << endl;*/

	int max = MaxSub[0];
	int maxId = Idx[0];
	int m = 0;

	for (int i = 0; i < n; i++)
	{
		if (MaxSub[i] > max)
		{
			max = MaxSub[i];
			maxId = Idx[i];
			m = A[i];
		}
	}
	

	cout << max << endl;
	cout << m << " ";

	while (maxId != -1)
	{
		cout << A[maxId] << " ";
		maxId = Idx[maxId];
	}
}