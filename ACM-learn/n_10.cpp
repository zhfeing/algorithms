///*1005*/
//#include <iostream>
//#include <cassert>
//#include <vector>
//#include <string>
//#include <cmath>
//#include <algorithm>
//#include <list>
//#include <queue>
//#include <set>
//
//using namespace std;
///*
//f(1) = 1, f(2) = 1, f(n) = (A * f(n - 1) + B * f(n - 2)) mod 7
//*/
//int main()
//{
//	int a, b, n;
//	while (cin >> a >> b >> n)
//	{
//		a %= 7;
//		b %= 7;
//		if (n == 0)
//		{
//			break;
//		}
//		int f_n_1 = 1;
//		int f_n_2 = 1;
//		int t;
//		if (a == 0 && b == 0 && n > 2)
//		{
//			f_n_2 = 0;
//			f_n_1 = 0;
//		}
//		else
//		{
//			for (int i = 0; i < n - 2; i += 2)
//			{
//				f_n_2 = (a * f_n_1 + b * f_n_2) % 7;
//				f_n_1 = (a * f_n_2 + b * f_n_1) % 7;
//				cout << f_n_2 << "\t" << f_n_1 << endl;
//			}
//		}
//		if (n % 2 == 0)
//		{
//			cout << f_n_1 << endl;
//		}
//		else
//		{
//			cout << f_n_2 << endl;
//		}
//	}
//	return 0;
//}
//
