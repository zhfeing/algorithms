/*1069*/
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

class Block
{
public:
	int x, y, z;
	Block()
	{
		x = 0;
		y = 0;
		z = 0;
	}
	Block(int x, int y, int z): 
		x(x), y(y), z(z){ }
	class Pred
	{
	public:
		bool operator()(const Block &l, const Block &r)
		{
			if (l.x == r.x)
			{
				return l.y > r.y;
			}
			else
			{
				return l.x > r.x;
			}
		}
	};
};

typedef vector<Block> Vblock;

int main()
{
	int i = 1;
	int n;
	Vblock blocks;
	vector<int> dp;

	blocks.reserve(30*6);
	dp.reserve(30*6);

	while (cin >> n)
	{
		if (n == 0)
		{
			break;
		}
		blocks.resize(6*n);
		int x, y, z;
		for (Vblock::iterator iter = blocks.begin(); iter != blocks.end(); )
		{
			cin >> x >> y >> z;
			iter->x = x; iter->y = y; iter->z = z;
			iter++;
			iter->x = x; iter->y = z; iter->z = y;
			iter++;
			iter->x = y; iter->y = x; iter->z = z;
			iter++;
			iter->x = y; iter->y = z; iter->z = x;
			iter++;
			iter->x = z; iter->y = x; iter->z = y;
			iter++;
			iter->x = z; iter->y = y; iter->z = x;
			iter++;
		}
		sort(blocks.begin(), blocks.end(), Block::Pred());
		
		dp.resize(6 * n);
		dp[0] = blocks[0].z;

		for (int j = 1; j < 6 * n; j++)
		{
			int q = 0;
			//int mh = 0;
			for (int k = 0; k < j; k++)
			{
				if (blocks[k].x > blocks[j].x && blocks[k].y > blocks[j].y)
				{
					q = max(q, dp[k]);
					//mh = blocks[k].z;
				}
			}
			dp[j] = q + blocks[j].z;
		}
		int ans = *max_element(dp.begin(), dp.end());
		blocks.clear();
		cout << "Case " << i++ << ": maximum height = " << ans << endl;
	}
	return 0;
}