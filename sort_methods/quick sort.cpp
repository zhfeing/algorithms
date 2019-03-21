#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <cassert>

using namespace std;
typedef std::vector<int> Vint;
typedef struct returnStruct
{
	int i;	//points the further poistion that key is less than piviot
	int j;	//points the near poistion that key is greater than piviot
	returnStruct()
	{
		i = -1;
		j = -1;
	}
	returnStruct(int i, int j)
	{
		this->i = i;
		this->j = j;
	}
}returnStruct;
typedef struct Bad_returnStruct{ }Bad_returnStruct;
void quickSort(Vint& data, int p, int q);//sort from data[p] to data[q]
returnStruct partition(Vint& data, int p, int q);//sort partitionally
void print(const Vint& data);
void initial(Vint& data);
inline void swap(int& a, int& b);
long long int count0 = 0;
const int Size = 10000;
Vint Data(Size);

int main()
{
	static int max;
	for (int k = 0; k < 10; k++)
	{
		initial(Data);
		//print(Data);
		quickSort(Data, 0, Data.size() - 1);
		print(Data);
		//cout << "Size is" << Size << endl;
		//cout << count0 << endl;
		if (max < count0)
			max = count0;
		count0 = 0;
	}
	cout << "max is " << max << endl;
	return 0;
}
void print(const Vint& data)
{
	for (int i = 0; i < data.size(); i++)
	{
		//printf("%d\t", data[i]);
	}
	//cout << endl;
}
inline void swap(int& a, int& b)
{
	if (a == b)
		return;
	int temp = a;
	a = b;
	b = temp;
}
void quickSort(Vint& data, int p, int q)
{
	if (p < q && p >= 0 && q < data.size())	//two or more element
	{
		returnStruct s = partition(data, p, q);
		if (s.i >= s.j)
			throw(Bad_returnStruct());
		quickSort(data, p, s.i);
		quickSort(data, s.j, q);
	}
}
returnStruct partition(Vint& data, int p, int q)
{
	//randomly choose a piviot
	srand(time(0));
	int key;
	key = rand() % (q - p + 1) + p;
	//key = p;
	int pivoit = data[key];
	swap(data[q], data[key]);

	int i, j, r;
	for (i = p - 1, j = p, r = p - 1; j < q; j++)
	{
		if (data[j] == pivoit)
		{
			swap(data[j], data[++r]);
		}
		else if (data[j] < pivoit)
		{
			swap(data[j], data[++r]);
			swap(data[r], data[++i]);
		}
		count0++;
	}
	swap(data[++r], data[q]);
	return returnStruct(i, r + 1);
}
void initial(Vint& data)
{
	srand(time(0));
	for (int i = 0; i < data.size(); i++)
	{
		data[i] = 1;
	}	
}