///*1013*/
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
//
//int main()
//{
//	string n;
//	while (cin >> n)
//	{
//		int sum = 0;
//		if (n == "0")
//		{
//			break;
//		}
//		for (string::iterator iter = n.begin(); iter != n.end(); iter++)
//		{
//			sum += *iter - '0';
//			if (sum >= 10)
//			{
//				sum = sum % 10 + sum / 10 % 10;
//			}
//		}
//		cout << sum << endl;
//	}
//	return 0;
//}