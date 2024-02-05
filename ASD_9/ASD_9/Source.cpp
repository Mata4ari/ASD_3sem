﻿#include <iostream>
#include<vector>
#include<algorithm>
#include <limits.h>
#include <Windows.h>
using namespace std;


#define V 5


#define GENES ABCDE
#define START 0


int child = 0;
int populationSize = 0;
int evoCount = 0;


int map[V][V] = { { INT_MAX, 25, 40, 31, 27},
				{ 5, INT_MAX, 17, 30, 25},
				{ 19, 15, INT_MAX, 6, 1},
				{ 9, 50, 24, INT_MAX, 6 },
				{ 22, 8, 7, 10, INT_MAX } };
struct individual {
	string gnome;
	int fitness;
};


int rand_num(int start, int end)
{
	int r = end - start;
	int rnum = start + rand() % r;
	return rnum;
}


bool repeat(string s, char ch)
{
	for (int i = 0; i < s.size(); i++) {
		if (s[i] == ch)
			return true;
	}
	return false;
}


string mutatedGene(string gnome)
{
	while (true) {
		int r = rand_num(1, V);
		int r1 = rand_num(1, V);
		if (r1 != r) {
			char temp = gnome[r];
			gnome[r] = gnome[r1];
			gnome[r1] = temp;
			break;
		}
	}
	return gnome;
}

string create_gnome()
{
	string gnome = "0";
	while (true) {
		if (gnome.size() == V) {
			gnome += gnome[0];
			break;
		}
		int temp = rand_num(1, V);
		if (!repeat(gnome, (char)(temp + 48)))
			gnome += (char)(temp + 48);
	}
	return gnome;
}

int cal_fitness(string gnome)
{

	int f = 0;
	for (int i = 0; i < gnome.size() - 1; i++) {
		if (map[gnome[i] - 48][gnome[i + 1] - 48] == INT_MAX)
			return INT_MAX;
		f += map[gnome[i] - 48][gnome[i + 1] - 48];
	}
	return f;
}

int cooldown(int temp)
{
	return (90 * temp) / 100;
}

bool lessthan(struct individual t1,
	struct individual t2)
{
	return t1.fitness < t2.fitness;
}

void TSPUtil(int map[V][V])
{
	int gen = 1;
	int gen_thres = evoCount;

	vector<struct individual> population;
	struct individual temp;

	for (int i = 0; i < populationSize; i++) {
		temp.gnome = create_gnome();
		temp.fitness = cal_fitness(temp.gnome);
		population.push_back(temp);
	}

	cout << "\nНачальная популяция: " << endl;
	cout << "Маршрут \tДлина маршрута\n";
	for (int i = 0; i < populationSize; i++)
		cout << population[i].gnome << "\t\t"
		<< population[i].fitness << endl;
	cout << "\n";

	int temperature = 10000;

	sort(population.begin(), population.end(), lessthan);

	while (temperature > 100 && gen <= gen_thres) {
		cout << endl << "Минимальный маршрут: " << population[0].gnome;
		cout << " Минимальная длина маршрута: " << population[0].fitness << "\n\n";

		/*cout << "\nòåêóùèé áóôåð: " << temperature << "\n";*/
		vector<struct individual> new_population;

		for (int i = 0; i < child; i++) {

			struct individual p1 = population[i];

			while (true)
			{
				string new_g = mutatedGene(p1.gnome);
				struct individual new_gnome;
				new_gnome.gnome = new_g;
				new_gnome.fitness = cal_fitness(new_gnome.gnome);

				if (new_gnome.fitness <= population[i].fitness) {
					new_population.push_back(new_gnome);
					break;
				}
				else {
					new_gnome.fitness = INT_MAX;
					new_population.push_back(new_gnome);
					break;
				}
			}
		}

		temperature = cooldown(temperature);
		for (int i = 0; i < child; i++)
		{
			population.push_back(new_population[i]);
		}
		sort(population.begin(), population.end(), lessthan);

		for (int i = 0; i < child; i++)
		{
			population.pop_back();
		}

		cout << "Номер популяции " << gen << " \n";
		cout << "Маршрут \tДлина маршрута\n";

		for (int i = 0; i < populationSize; i++)
			cout << population[i].gnome << "\t\t"
			<< population[i].fitness << endl;
		gen++;
	}
	cout << "\n\n";
}

int main()
{
	setlocale(LC_ALL, "ru");
	cout << "Введите размер популяции: "; cin >> populationSize;
	cout << "Введите количество наследников: "; cin >> child;
	cout << "Введите количество мутаций: "; cin >> evoCount;
	TSPUtil(map);
}