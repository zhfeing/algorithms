/*1004*/
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

vector<string> Table;
vector<int> Count_string;

int string_in_table(const string &s)
{
	for (int i = 0; i < Table.size(); i++)
	{
		if (s == Table[i])
			return i;
	}
	return -1;
}

typedef struct
{
	bool operator()(const int &left, const int &right)
	{
		return left < right;
	}
}Pred;

int main()
{
	int N;
	vector<string> input(1000);
	while (cin >> N)
	{
		if (N == 0)
			break;
		for (int i = 0; i < N; i++)
		{
			cin >> input[i];
		}
		for (int i = 0; i < N; i++)
		{
			int code;
			code = string_in_table(input[i]);
			if (code == -1)
			{
				Table.push_back(input[i]);
				Count_string.push_back(1);
			}
			else
			{
				Count_string[code]++;
			}
		}
		vector<int>::iterator max = max_element(Count_string.begin(), Count_string.end(), Pred());
		cout << Table[max - Count_string.begin()] << endl;
		Table.resize(0);
		Count_string.resize(0);
	}
	return 0;
}
