/*1159*/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <list>
#include <queue>
#include <set>

using namespace std;

int main()
{
	string s1, s2;
	while (cin >> s1 >> s2)
	{
		int m = s1.size();
		int n = s2.size();
		if (m == 0 || n == 0)
		{
			cout << 0 << endl;
			continue;
		}
		vector<int> dp1(m), dp2(m);
		// calculate the first row
		dp1[0] = int(s1[0] == s2[0]);
		for (int i = 1; i < m; i++)
		{
			dp1[i] = max(dp1[i - 1], int(s1[i] == s2[0]));
		}
		// calculate the table row by row
		bool base_is_1 = true;
		for (int r = 1; r < n; r++)
		{
			if (base_is_1)	// base line is dp1
			{
				dp2[0] = max(dp1[0], int(s1[0] == s2[r]));
				for (int i = 1; i < m; i++)
				{
					if (s1[i] == s2[r])
					{
						dp2[i] = 1 + dp1[i - 1];
					}
					else
					{
						dp2[i] = max(dp2[i - 1], dp1[i]);
					}
				}
			}
			else	// base line is dp2
			{
				dp1[0] = max(dp2[0], int(s1[0] == s2[r]));
				for (int i = 1; i < m; i++)
				{
					if (s1[i] == s2[r])
					{
						dp1[i] = 1 + dp2[i - 1];
					}
					else
					{
						dp1[i] = max(dp1[i - 1], dp2[i]);
					}
				}
			}
			base_is_1 = !base_is_1;
		}
		if (base_is_1)
		{
			cout << dp1.back() << endl;
		}
		else
		{
			cout << dp2.back() << endl;
		}
	}
	return 0;
}