/*1203*/
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

typedef vector<int> Vint;
typedef vector<float> Vfloat;
typedef vector<double> Vdouble;


float get_max_prob(const Vint &cost, const Vfloat &prob, const int total_money)
{
	int m = cost.size();
	Vfloat prob_record(total_money + 1, 0);
	Vfloat prob_record_old(total_money + 1, 0);
	for (int i = 0; i < m; i++)
	{
		// calculate record table
		for (int left = 0; left <= total_money; left++)
		{
			if (left < cost[i])
			{
				prob_record[left] = prob_record_old[left];
			}
			else
			{
				float prob1 = prob_record_old[left];
				float prob2 = prob_record_old[left - cost[i]] * (1 - prob[i]) + prob[i];
				prob_record[left] = max(prob1, prob2);
			}
		}
		prob_record_old.assign(prob_record.begin(), prob_record.end());
	}
	return prob_record[total_money];
}

int main()
{
	int m, n;
	while (cin >> n >> m)
	{
		if (n == 0 && m == 0)
		{
			break;
		}
		Vint collage_cost(m);
		Vfloat collage_prob(m);
		for (int i = 0; i < m; i++)
		{
			cin >> collage_cost[i] >> collage_prob[i];
		}
		int c = get_max_prob(collage_cost, collage_prob, n)*1000 + 0.5;
		printf("%.1f%%\n", c/10.0);
	}
	return 0;
}