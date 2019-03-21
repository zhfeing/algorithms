// /*1159*/
// #include <iostream>
// #include <vector>
// #include <string>
// #include <algorithm>
// #include <list>
// #include <queue>
// #include <set>
 
// using namespace std;

// class Node
// {
// public:
// 	char oper;
// 	char edit_char;
// 	int pos;
// };
// class OutPut
// {
// public:
// 	char oper;
// 	int pos;
// 	char c;
// 	OutPut(const char oper, const int pos, const char c)
// 		:oper(oper), pos(pos), c(c){ }
// };

// int main()
// {
// 	string s1, s2;
// 	while (cin >> s1 >> s2)
// 	{
// 		int m = s1.length();
// 		int n = s2.length();
// 		vector<vector<int>> dp(m + 1);
// 		vector<vector<Node>> trace(m + 1);
// 		// ititial
// 		for (int i = 0; i <= m; i++)
// 		{
// 			dp[i].resize(n + 1, 0);
// 			trace[i].resize(n + 1);
// 		}

// 		dp[0][0] = 0;
// 		trace[0][0].oper = 'n';
// 		// initial the table
// 		for (int i = 1; i <= m; i++)
// 		{
// 			dp[i][0] = dp[i - 1][0] + 1;
// 			trace[i][0].oper = 'd';
// 			trace[i][0].edit_char = s1[i - 1];
// 			trace[i][0].pos = i;
// 		}
// 		for (int j = 1; j <= n; j++)
// 		{
// 			dp[0][j] = dp[0][j - 1] + 1;
// 			trace[0][j].oper = 'i';
// 			trace[0][j].edit_char = s2[j - 1];
// 			trace[0][j].pos = j;
// 		}
// 		for (int i = 1; i <= m; i++)
// 		{
// 			for (int j = 1; j <= n; j++)
// 			{
// 				vector<int> cost(4, INT_MAX);	// 0: insert, 1: delete, 2: repleace, 3: nothing
// 				if (s1[i - 1] == s2[j - 1])	// can do nothing
// 				{
// 					cost[3] = dp[i - 1][j - 1];
// 				}
// 				else
// 				{
// 					cost[0] = dp[i][j - 1] + 1;
// 					cost[1] = dp[i - 1][j] + 1;
// 					cost[2] = dp[i - 1][j - 1] + 1;
// 				}
// 				int index = min_element(cost.begin(), cost.end()) - cost.begin();
// 				dp[i][j] = cost[index];
// 				switch (index)
// 				{
// 				case 0:
// 					trace[i][j].oper = 'i';
// 					trace[i][j].edit_char = s2[j - 1];
// 					trace[i][j].pos = max(i, j);
// 					break;
// 				case 1:
// 					trace[i][j].oper = 'd';
// 					trace[i][j].edit_char = s1[i - 1];
// 					trace[i][j].pos = max(i, j);
// 					break;
// 				case 2:
// 					trace[i][j].oper = 'r';
// 					trace[i][j].edit_char = s2[j - 1];
// 					trace[i][j].pos = max(i, j);
// 					break;
// 				case 3:
// 					trace[i][j].oper = 'n';
// 					break;
// 				}
// 			}
// 		}
// 		cout << dp[m][n] << endl;
// 		list<OutPut> count_list;
// 		int i = m;
// 		int j = n;
// 		while(i || j)
// 		{
// 			switch (trace[i][j].oper)
// 			{
// 			case 'i':
// 				count_list.push_front(OutPut(trace[i][j].oper, trace[i][j].pos, trace[i][j].edit_char));
// 				j--;
// 				break;
// 			case 'd':
// 				count_list.push_front(OutPut(trace[i][j].oper, trace[i][j].pos, trace[i][j].edit_char));
// 				i--;
// 				break;
// 			case 'n':
// 				i--;
// 				j--;
// 				break;
// 			case 'r':
// 				count_list.push_front(OutPut(trace[i][j].oper, trace[i][j].pos, trace[i][j].edit_char));
// 				i--;
// 				j--;
// 				break;
// 			}
// 		}
// 		int deep_change = 0;
// 		i = 1;
// 		for (auto iter = count_list.begin(); iter != count_list.end(); iter++)
// 		{
// 			switch (iter->oper)
// 			{
// 			case 'i':
// 				cout << i << " Insert " << iter->pos + deep_change << "," << iter->c << endl;
// 				break;
// 			case 'd':
// 				cout << i << " Delete " << iter->pos + deep_change-- << endl;
// 				break;
// 			case 'r':
// 				cout << i << " Replace " << iter->pos + deep_change << "," << iter->c << endl;
// 				break;
// 			}
// 			i++;
// 		}
// 	}
// 	return 0;
// }