#include <iostream>
#include <string>
#include <vector>
int cnt;
using std::string;
typedef std::vector<std::vector<int>> Vint2;
bool isPal(string &v, int i, int j)
{
	while (i < j)
	{
		if (v[i] != v[j])
		{
			return false;
		}
		else
		{
			i++;
			j--;
		}
		cnt++;
	}
	return true;
}
int longestPal(string &v, int &recordBegin, int &recordEnd)
{
	int maxLength = v.size();
	int maxPalNumber = 0;
	for (int length = 1; length <= maxLength; length++)
	{
		for (int begin = 0; begin <= maxLength - length; begin++)
		{
			int end = begin + length - 1;
			if (isPal(v, begin, end))
			{
				if (maxPalNumber < length)
				{
					maxPalNumber = length;
					recordBegin = begin;
					recordEnd = end;
				}
			}
		}
	}
	return maxPalNumber;
}
void printB(Vint2 &b)
{
	for (int i = 0; i < b.size(); i++)
	{
		for (int j = 0; j < b[i].size(); j++)
		{
			std::cout << b[i][j] << " ";
		}
		std::cout << std::endl;
	}
}
string findLMS(string &s, int l, int r)
{
	if (l < 0 || r >= s.size())
	{
		return string();
	}
	int m = l + 2;
	int n = s.size() - r + 1;
	//create record matrix
	Vint2 c(n);
	for (int i = 0; i < n; i++)
	{
		c[i].resize(m);
	}
	//initial matrix
	for (int i = 0; i < n; i++)
		c[i][0] = 0;
	for (int j = 0; j < m; j++)
		c[0][j] = 0;
	//create a record table bottom-up
	for (int i = 1; i < n; i++)
	{
		for (int j = 1; j < m; j++)
		{
			if (s[l - j + 1] == s[r + i - 1])
				//a common character
			{
				c[i][j] = c[i - 1][j - 1] + 1;
			}
			else if (c[i][j - 1] >= c[i - 1][j])
			{
				c[i][j] = c[i][j - 1];
			}
			else
			{
				c[i][j] = c[i - 1][j];
			}
			cnt++;
		}
	}
	//printB(c);
	int i = n - 1;
	int j = m - 1;
	string lms;
	while (i != 0 && j != 0)
	{
		if (c[i - 1][j] > c[i][j - 1])
		{
			i--;
		}
		else if (c[i - 1][j] < c[i][j - 1])
		{
			j--;
		}
		else if ((c[i - 1][j] == c[i][j - 1]) &&
			(c[i - 1][j - 1] < c[i][j]))
		{
			lms.push_back(s[l - j + 1]);
			i--;
			j--;
		}
		else
		{
			i--;
		}
	}
	return lms;
}

string findLPal(string &s)
{
	string LPal;
	int maxLength = 0;
	for (int c = 0; c < s.size(); c++)
	{
		string temp = findLMS(s, c - 1, c + 1);
		if (temp.size() > maxLength)
		{
			maxLength = temp.size();
			LPal = temp;
			LPal.push_back(s[c]);
		}
	}
	int lpal_length = LPal.size() - 2;
	for (int i = lpal_length; i >= 0; i--)
	{
		LPal.push_back(LPal[i]);
	}
	return LPal;
}

int main()
{
	string v;
	int len = 100000;
	for (int i = 0; i < len; i++)
		v.push_back(rand());
	int b, e;
	longestPal(v, b, e);
	std::cout << cnt << std::endl;
}