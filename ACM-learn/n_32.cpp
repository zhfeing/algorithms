/*1028*/
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
#include <limits>

using namespace std;

int main()
{
	int N;
	while (cin >> N)
	{
		vector<vector<int>> dp(N);
		for (auto iter = dp.begin(); iter != dp.end(); iter++)
		{
			iter->resize(N, 0);
		}
		for (int n = 1; n <= N; n++)
		{
			for (int k = 1; k <= n; k++)
			{
				if (k == 1 || n == k)
				{
					dp[k-1][n-1] = 1;
				}
				else
				{
					int sum = 0;
					for (int p = 1; p <= min(k, n - k); p++)
					{
						sum += dp[p-1][n - k-1];
					}
					dp[k-1][n-1] = sum;
				}
			}
		}
		int total = 0;
		for (int i = 0; i < N; i++)
		{
			total += dp[i][N - 1];
		}
		cout << total << endl;
	}
}