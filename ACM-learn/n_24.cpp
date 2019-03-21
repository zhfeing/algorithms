/*1020*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cassert>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <list>
#include <queue>
#include <set>
#include <cstdlib>
#include <cmath>

using namespace std;

int main()
{
	int n;
	string s;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> s;
		char last = 0;
		int count = 0;
		for (string::iterator iter = s.begin(); iter != s.end(); iter++)
		{
			if (*iter == last)
			{
				count++;
			}
			else
			{
				if (count != 0 && last != 0)
				{
					cout << count + 1 << last;
				}
				else if (last != 0)
				{
					cout << last;
				}
				count = 0;
			}
			last = *iter;
		}
		if (count != 0 && last != 0)
		{
			cout << count + 1 << last;
		}
		else if (last != 0)
		{
			cout << last;
		}
		cout << endl;
	}
	return 0;
}