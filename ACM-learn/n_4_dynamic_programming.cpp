/*1003*/
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cassert>
#include <iostream>


using namespace std;

typedef vector<int> Vint;
typedef struct
{
	int result;
	int begin;
	int end;
} ResultStruct;

vector<ResultStruct> dp;


typedef struct
{
	bool operator()(const ResultStruct& lhs, const ResultStruct& rhs)
	{
		return lhs.result < rhs.result;
	}
}VectorPred;

void MSS(const Vint & v, int end)
{
	assert(end >= 0 && end < v.size());
	if (end == 0)
	{
		dp[0] = ResultStruct{ v[0], 0, 0 };
		return;
	}
	if (dp[end - 1].result >= 0)
	{
		dp[end] = ResultStruct{ dp[end - 1].result + v[end], dp[end - 1].begin, end };
		return;
	}
	else
	{
		dp[end] = ResultStruct{ v[end], end, end };
		return;
	}
}

ResultStruct max_subsequence_sum(const Vint & v)
{
	dp.resize(v.size());
	for (int i = 0; i < v.size(); i++)
	{
		MSS(v, i);
	}
	vector<ResultStruct>::iterator max = max_element(dp.begin(), dp.end(), VectorPred());
	return *max;
}

int main()
{
	vector<Vint> input(20);
	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		int m;
		cin >> m;
		input[i].resize(m);
		for (int j = 0; j < m; j++)
		{
			cin >> input[i][j];
		}
	}
	vector<ResultStruct> res(20);
	for (int i = 0; i < n; i++)
	{
		res[i] = max_subsequence_sum(input[i]);
		cout << "Case " << i + 1 << ":" << endl;
		cout << res[i].result << " " << res[i].begin + 1 << " " << res[i].end + 1 << endl;
		if (i != n - 1)
		{
			cout << endl;
		}
	}
	//getchar();
	//getchar();
	//getchar();
	return 0;
}



















#include <iostream>  
using namespace std;

int main()
{
	int t;
	cin >> t;
	for (int i = 0; i<t; i++)
	{
		int n;
		cin >> n;
		int sum = 0, max = -99999;
		int curhead = 1, rear = 1, head = 1;
		for (int j = 0; j<n; j++)
		{
			int temp;
			cin >> temp;
			if (sum<0)
			{
				curhead = j + 1;
				sum = temp;

			}
			else
			{
				sum += temp;
			}
			if (sum>max)
			{
				rear = j + 1;
				head = curhead;
				max = sum;
			}
		}
		cout << "Case " << i + 1 << ":" << endl;
		cout << max << ' ' << head << ' ' << rear << endl;
		if (i != t - 1)
			cout << endl;
	}
	getchar();
	getchar();
	getchar();
	getchar();
}

