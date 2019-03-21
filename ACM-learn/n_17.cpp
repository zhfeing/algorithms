///*1009*/
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
//typedef struct ProbStruct
//{
//	int J, F;
//	double P;
//
//}ProbStruct;
//typedef struct Pred
//{
//	bool operator()(const ProbStruct &l, const ProbStruct &r)
//	{
//		return l.P > r.P;
//	}
//}Pred;
//
//double get_max_JB(vector<ProbStruct> &pro, const int M)
//{
//	for (int i = 0; i < pro.size(); i++)
//	{
//		pro[i].P = pro[i].J / double(pro[i].F);
//	}
//	sort(pro.begin(), pro.end(), Pred());
//	int left = M;
//	double got_food = 0;
//	for (int item = 0; item < pro.size(); item++)
//	{
//		if (left > pro[item].F)
//		{
//			got_food += pro[item].J;
//			left -= pro[item].F;
//		}
//		else  // running out of money
//		{
//			got_food += left / double(pro[item].F)*pro[item].J;
//			break;
//		}
//	}
//	return got_food;
//}
//
//int main()
//{
//	int M, N; 
//	vector<ProbStruct> pro;
//	pro.reserve(1000);
//	while (cin >> M >> N)
//	{
//		if (M == -1 && N == -1)
//		{
//			break;
//		}
//		pro.resize(N);
//		for (int i = 0; i < N; i++)
//		{
//			cin >> pro[i].J >> pro[i].F;
//		}
//		double ans = get_max_JB(pro, M);
//		printf("%.3lf\n", ans);
//	}
//	return 0;
//}