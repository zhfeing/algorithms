#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
#include <string>

using namespace std;

int space(const int M, int i, int j, const vector<vector<int>> &L)
{
	if (i > j)
	{
		return 0;
	}
	int tmp = M - j + i - L[i][j];
	return tmp < 0 ? INT_MAX : tmp;
}

int main()
{
	int n, M;
	while (cin >> n >> M)
	{
		if (n == 0)
		{
			break;
		}
		vector<int> lengths(n);
		for (vector<int>::iterator iter = lengths.begin(); iter != lengths.end(); iter++)
		{
			cin >> *iter;
		}
		// check illegal instance
		int max_letter_length = *max_element(lengths.begin(), lengths.end());
		if (max_letter_length > M)
		{
			cout << "a letter is too length" << endl;
			continue;
		}

		vector<vector<int>> L(n);	// record length from letter i to letter j
		for (vector<vector<int>>::iterator iter = L.begin(); iter != L.end(); iter++)
		{
			iter->resize(n, INT_MAX);
		}
		for (int i = 0; i < n; i++)
		{
			L[i][i] = lengths[i];
			for (int j = i + 1; j < n; j++)
			{
				L[i][j] = L[i][j - 1] + lengths[j];
			}
		}

		vector<int>dp(n);		// minium space^3 of blanks from letter k to letter n
		dp[n - 1] = 0;
		for (int k = n - 1; k >= 0; k--)
		{
			int q = INT_MAX;
			for (int j = k + 1; j <= n; j++)		// cut from k + 1
			{
				int s = space(M, k, j - 1, L);
				if (s != INT_MAX)
				{
					if (j == n)
					{
						q = 0;
					}
					else
					{
						q = min(q, dp[j] + s*s*s);
					}
				}
				else
				{
					break;
				}
			}
			dp[k] = q;
		}
		cout << dp[0] << endl;
	}
	return 0;
}

/*
6 8
4 3 1 5 2 6
*/