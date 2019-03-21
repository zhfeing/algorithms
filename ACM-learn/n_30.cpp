///*1025*/
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
//#include <limits>
//
//using namespace std;
//
//#define MAX_N 500000
//
//int P[MAX_N], LIS[MAX_N], Record[MAX_N];
//const int IntMax = numeric_limits<int>::max();
//
//// raise key
//int *binary_search(int *begin, int *end, const int key)
//{
//	int *b = begin;
//	int *e = end;
//	while (b < e - 1)
//	{
//		int *mid = b + (e - b)/2;
//		if (*mid > key)
//		{
//			e = mid;
//		}
//		else
//		{
//			b = mid;
//		}
//	}
//	if (key > *b)
//	{
//		return e;
//	}
//	else
//	{
//		return b;
//	}
//}
//
//int main()
//{
//	int n;
//	int case_id = 1;
//	while (cin >> n)
//	{
//		int p, r;
//		for (int i = 0; i < n; i++)
//		{
//			scanf("%d", &p);
//			scanf("%d", &r);
//			P[p - 1] = r - 1;
//			Record[i] = IntMax;
//		}
//
//		int max_roads = 1;
//		// it just a LIS problem
//		LIS[0] = 0;
//		Record[0] = P[0];
//		for (int i = 1; i < n; i++)
//		{
//			int *k = binary_search(Record, Record + max_roads, P[i]);
//			int index = k - Record;
//			LIS[i] = index;
//			max_roads = max(max_roads, LIS[i] + 1);
//			if (P[i] < *k)
//			{
//				*k = P[i];
//			}
//		}
//		cout << "Case " << case_id << ":\n" << "My king, at most " << max_roads;
//		if (max_roads == 1)
//			cout << " road can be built." << endl;
//		else
//			cout << " roads can be built." << endl;
//		cout << endl;
//		case_id++;
//	}
//	return 0;
//}
//
