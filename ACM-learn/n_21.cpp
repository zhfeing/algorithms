/*10292*/
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

inline bool is_vowels(char c)
{
	if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')
	{
		return true;
	}
	else
	{
		return false;
	}
}

int main()
{
	string s;
	while (cin >> s)
	{
		if (s == "end")
		{
			break;
		}
		bool c_vowels = false;
		int c_cvow = 0;
		int c_ccon = 0;
		char last_c = 0;
		bool flag = false;

		for (string::iterator iter = s.begin(); iter != s.end(); iter++)
		{
			if (is_vowels(*iter))
			{
				c_vowels = true;
				if (is_vowels(last_c) && last_c != 0)
				{
					c_cvow++;
				}
				else
				{
					c_cvow = 1;
				}
				c_ccon = 0;
			}
			else
			{
				if (!is_vowels(last_c) && last_c != 0)
				{
					c_ccon++;
				}
				else
				{
					c_ccon = 1;
				}
				c_cvow = 0;
			}
			if (last_c == *iter && (last_c != 'e' && last_c != 'o'))
			{
				cout << "<" << s << "> is not acceptable." << endl;
				flag = true;
				break;
			}
			else if (c_cvow == 3 || c_ccon == 3)
			{
				cout << "<" << s << "> is not acceptable." << endl;
				flag = true;
				break;
			}
			last_c = *iter;
		}
		if (!c_vowels && !flag)
		{
			cout << "<" << s << "> is not acceptable." << endl;
		}
		else if(!flag)
		{
			cout << "<" << s << "> is acceptable." << endl;
		}
	}
	return 0;
}