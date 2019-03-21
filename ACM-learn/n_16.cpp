/*1024*/
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

inline long long max(const long long &x1, const long long &x2)
{
	return x1 > x2 ? x1 : x2;
}


int main()
{
	int m, n;
	vector<int> a;
	vector<long long>F;
	vector<long long>G;
	a.reserve(1000000);
	F.reserve(1000000);
	G.reserve(1000000);
	while (cin >> m >> n)
	{
		a.resize(n);
		F.resize(n);
		G.resize(n);
		for (int i = 0; i < n; i++)
			scanf("%d", &a[i]);
		for (int i = 0; i < n; i++)
		{
			F[i] = i == 0 ? a[i] : a[i] + max(F[i - 1], 0);
			G[i] = i == 0 ? LLONG_MIN : max(F[i - 1], G[i - 1]);
			//cout << "F_" << i << " " << F[i] << " G_" << i << " " << G[i] << endl;
		}
		//cout << endl;
		for (int i = 1; i < m; i++)
		{
			for (int j = i; j < n; j++)
			{
				if (j == i)
				{
					F[j] = F[j - 1] + a[j];
				}
				else
				{
					F[j] = max(F[j - 1], G[j]) + a[j];
				}
			}
			G[i + 1] = F[i];
			for (int j = i + 2; j < n; j++)
			{
				G[j] = max(G[j - 1], F[j - 1]);
			}
		}
		long long max_sum = *max_element(F.begin() + m - 1, F.end());
		cout << max_sum << endl;
	}
	return 0;
}