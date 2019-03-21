#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>


using namespace std;


int main()
{
	unsigned n;
	while (cin >> n)
	{
		cout << n * (n + 1) / 2 << endl << endl;
	}
	return 0;
}