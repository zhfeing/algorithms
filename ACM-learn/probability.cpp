#include <random>
#include <vector>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main()
{
	constexpr int N_repeat = 100000;
	constexpr int N_play_max = 10000;


	ofstream file("count.txt");
	if (!file.is_open())
	{
		cout << "open file failed" << endl;
		return -1;
	}

	for (int i = 1; i <= N_play_max; i++)
	{
		int n_loose = 0;
		double loose_pr;

		for (int j = 1; j <= N_repeat; j++)
		{
			int money_now = 1;
			for (int play_id = 1; play_id <= i; play_id++)
			{
				bool win = rand() % 2;
				if (win)
				{
					money_now++;
				}
				else
				{
					money_now--;
					if (money_now < 0)
					{
						n_loose++;
						break;
					}
				}
			}
		}
		loose_pr = n_loose / (double)N_repeat;
		file << loose_pr << endl;
		cout << "i: " << i << "pr=" << loose_pr << endl;
	}
	return 0;
}