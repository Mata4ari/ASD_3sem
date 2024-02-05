#include <iostream>
#include <vector>
using namespace std;


void Hanoi1(int n, vector<int> v)
{
	if (n <= 0)                                   
		return;
	auto it = v.begin();
	it++;
	reverse(it, v.end());
	Hanoi1(n - 1,v);
	reverse(it, v.end());
	cout << v[0] << "->" << v[1] << ";" << endl;
	reverse(v.begin(), v.end());
	Hanoi1(n - 1,v);                         

	                                        
}

void main()
{
	setlocale(LC_CTYPE, "ru");
	int n, k=3;
	cout << "¬ведите н дисков" << endl;
	cin >> n;
	vector<int> v;
	for (int i = 1; i <= k; i++)
		v.push_back(i);
	
	Hanoi1(n,v);
	
	
}