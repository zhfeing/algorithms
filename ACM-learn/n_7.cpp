/*2081*/
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;


int main()
{
	int N;
	cin >> N;
	vector<string> number(N);
	for (int i = 0; i < N; i++)
	{
		cin >> number[i];
		string short_number("6");
		short_number.append(number[i].begin() + 6, number[i].end());
		cout << short_number << endl;
	}
	//getchar();
	//getchar();
	//getchar();
	//getchar();
}
