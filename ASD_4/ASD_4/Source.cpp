#include <iostream>
using namespace std;

void main()
{
	const int N = 6;
	int C[6][6] = { {0,28,21,59,12,27},
				  {7,0,24,INT_MAX,21,9},
				  {9,32,0,13,11,INT_MAX},
				  {8,INT_MAX,5,0,16,INT_MAX},
				  {14,13,15,10,0,22},
				  {15,18,INT_MAX,INT_MAX,6,0}
	};
	int S[6][6] = { {0,2,3,4,5,6},
					{1,0,3,4,5,6},
					{1,2,0,4,5,6},
					{1,2,3,0,5,6},
					{1,2,3,4,0,6},
					{1,2,3,4,5,0}
	};
	for (int m = 0; m < N; m++) 
	{
		for (int i = 0; i < 6; i++)
		{
			for (int j = 0; j < 6; j++)
			{
				if (C[i][m] + C[m][j] < C[i][j])
				{
					C[i][j] = C[i][m] + C[m][j];
					S[i][j] = m+1;
				}
			}
		}
	}

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cout << C[i][j] << " ";
		}
		cout << "\n";
	}
	cout << endl;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cout << S[i][j] << " ";
		}
		cout << "\n";
	}
}