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
//#include <cstdlib>
//#include <cmath>
//
//using namespace std;
//typedef vector<int> Vint;
//
//typedef struct Pred
//{
//	bool operator()(const long long &l, const long long &r)
//	{
//		return l < r;
//	}
//}Pred;
//
//void MMS(const Vint &v, int end, vector<long long> &MMS_table)
//{
//	int flag = v[end];
//	MMS_table[end] = flag;
//	if (end == 0)
//	{
//		return;
//	}
//
//	long long max_sum = LLONG_MIN;
//	for (int i = 0; i < end; i++)
//	{
//		if (v[i] < flag)
//		{
//			if (max_sum < MMS_table[i])
//			{
//				max_sum = MMS_table[i];
//			}
//		}
//	}
//	if (max_sum < 0)
//	{
//		MMS_table[end] = max_sum > flag ? max_sum : flag;
//	}
//	else
//	{
//		MMS_table[end] = flag > 0 ? flag + max_sum : max_sum;
//	}
//}
//
//
//long long max_monotone_subsequence_sum(const Vint &v)
//{
//	vector<long long> MMSS_table(v.size());
//	for (int i = 0; i < v.size(); i++)
//	{
//		MMS(v, i, MMSS_table);
//	}
//	return *max_element(MMSS_table.begin(), MMSS_table.end(), Pred());
//}
//
//int main()
//{
//	int N;
//	while (cin >> N)
//	{
//		Vint l;
//		if (N == 0)
//		{
//			break;
//		}
//		int a;
//		for (int i = 0; i < N; i++)
//		{
//			cin >> a;
//			l.push_back(a);
//		}
//		// here comes the algorithm
//		cout << max_monotone_subsequence_sum(l) << endl;
//	}
//	return 0;
//}