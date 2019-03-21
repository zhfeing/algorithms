/*1003*/
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cassert>


using namespace std;

typedef vector<int> Vint;
typedef struct
{
	int result;
	int begin;
	int end;
} ResultStruct;

ResultStruct max_sum_contain_center(const Vint &s, int c, int begin, int end)
{
	int sum = s[c];
	int start = c;
	int stop = c;
	int max_sum = sum;
	for (int i = c - 1; i >= begin; i--)
	{
		if (sum + s[i] >= max_sum)
		{
			start = i;
			max_sum = sum + s[i];
		}
		sum = sum + s[i];
	}
	sum = max_sum;
	for (int j = c + 1; j < end; j++)
	{
		if (sum + s[j] >= max_sum)
		{
			stop = j;
			max_sum = sum + s[j];
		}
		sum = sum + s[j];
	}
	return ResultStruct{ max_sum, start, stop + 1 };
}

ResultStruct max_sum_subsequence(const Vint &s, int begin, int end)
{
	assert(begin < end);
	if (begin == end - 1)
	{
		return ResultStruct{ s[begin], begin, end };
	}
	int c = (begin + end) / 2;
	ResultStruct r2 = max_sum_contain_center(s, c, begin, end);
	ResultStruct r1 = max_sum_subsequence(s, begin, c);

	if (c + 1 != end)
	{
		ResultStruct r3 = max_sum_subsequence(s, c + 1, end);
		if (r1.result > r3.result)
		{
			if (r1.result > r2.result)
			{
				return r1;
			}
			else if (r1.result < r2.result)
			{
				return r2;
			}
			else
			{
				if (r1.end - r1.begin >= r2.end - r2.begin)
				{
					return r1;
				}
				else
				{
					return r2;
				}
			}
		}
		else
		{
			if (r3.result > r2.result)
			{
				return r3;
			}
			else if (r3.result < r2.result)
			{
				return r2;
			}
			else
			{
				if (r3.end - r3.begin >= r2.end - r2.begin)
				{
					return r3;
				}
				else
				{
					return r2;
				}
			}
		}
	}
	else
	{
		if (r1.result > r2.result)
		{
			return r1;
		}
		else if (r1.result < r2.result)
		{
			return r2;
		}
		else
		{
			if (r1.end - r1.begin >= r2.end - r2.begin)
			{
				return r1;
			}
			else
			{
				return r2;
			}
		}
	}

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
		res[i] = max_sum_subsequence(input[i], 0, input[i].size());
		cout << "Case " << i + 1 << ":" << endl;
		cout << res[i].result << " " << res[i].begin + 1 << " " << res[i].end << endl;
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

