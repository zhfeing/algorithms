/*10292*/
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
int ints[999999];

int main()
{
	int N;
	while (cin >> N)
	{
		for (int i = 0; i < N; i++)
		{
			scanf("%d", ints + i);
		}
		sort(ints, ints + N);
		cout << ints[(N - 1) / 2] << endl;
	}
	return 0;
}