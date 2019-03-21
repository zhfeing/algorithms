///*1042*/
//#define _CRT_SECURE_NO_WARNINGS
//#include <iostream>
//#include <cassert>
//#include <vector>
//#include <string>
//#include <cmath>
//#include <algorithm>
//#include <list>
//#include <queue>
//#include <set>
//#include <cstdlib>
//#include <cmath>
//
//using namespace std;
//#define SS 10000
//
//int main()
//{
//	int n;
//	int res[SS];
//	while (cin >> n)
//	{
//		int p = 1;
//		for (int i = 0; i < SS; i++)
//			res[i] = 0;
//		res[0] = 1;
//
//		while (n > 1)
//		{
//			int c = 0, s;
//			for (int i = 0; i < p; i++)
//			{
//				s = res[i] * n + c;
//				res[i] = s % 10000;
//				c = s / 10000;
//			}
//			if (c != 0)
//			{
//				res[p] = c;
//				p++;
//			}
//			n--;
//		}
//		printf("%d", res[p - 1]);
//		for (int i = p - 2; i >= 0; i--)
//		{
//			printf("%04d", res[i]);
//		}
//		cout << endl;
//	}
//	return 0;
//}