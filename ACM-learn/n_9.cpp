///*2062*/
//#include <iostream>
//#include <fstream>
//#include <vector>
//#include <string>
//#include <algorithm>
//#include <set>
//#include <list>
//
//using namespace std;
//
//vector<unsigned long long> A(20); // increase 1 
//
//void initial()
//{
//	A[0] = 0;
//	for (int i = 1; i < 20; i++)
//	{
//		A[i] = i*(A[i - 1] + 1);
//	}
//}
//void do_something(int n, unsigned long long m)
//{
//	vector<int> s(n + 1);
//	for (int i = 0; i <= n; i++)
//	{
//		s[i] = i;
//	}
//	while (n != 0)
//	{
//		unsigned long long b = A[n - 1] + 1;
//		int index = (m - 1) / b + 1;
//		cout << s[index];
//		s.erase(s.begin() + index);
//		if ((m - 1) % b == 0)
//		{
//			cout << endl;
//			break;
//		}
//		else
//		{
//			m = (m - 1) % b;
//			cout << " ";
//		}
//		n--;
//	}
//	return;
//}
//// 6613313319248080000
//
//int main()
//{
//	initial();
//	int n;
//	unsigned long long m;
//	while (cin >> n >> m)
//	{
//		do_something(n, m);
//	}
//}
