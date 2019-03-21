///*2031*/
//#include <iostream>
//#include <fstream>
//#include <vector>
//#include <string>
//#include <algorithm>
//
//using namespace std;
//
//char Table[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
//
//int main()
//{
//	int n, r;
//	while (cin >> n >> r)
//	{
//		if (n < 0)
//		{
//			cout << '-';
//			n = -n;
//		}
//		else if (n == 0)
//		{
//			cout << "0" << endl;
//			continue;
//		}
//		vector<int>bit;
//		int b;
//		while (n)
//		{
//			b = n % r;
//			bit.push_back(b);
//			n /= r;
//		}
//		for (auto iter = bit.rbegin(); iter != bit.rend(); iter++)
//		{
//			cout << Table[*iter];
//		}
//		cout << endl;
//	}
//	return 0;
//}