//#include <iostream>
//#include <vector>
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
//	int n;
//	cin >> n;
//	vector<int> nums(n);
//	for (vector<int>::iterator iter = nums.begin(); iter < nums.end(); iter++)
//	{
//		cin >> *iter;
//	}
//	int min_var = INT_MAX;
//	for (int p = 0; p < n; p++)
//	{
//		for (int i = 0; i < p; i++)
//		{
//			min_var = abs(nums[i] - nums[p]) < min_var ? abs(nums[i] - nums[p]) : min_var;
//		}
//		for (int i = p + 1; i < n; i++)
//		{
//			min_var = abs(nums[i] - nums[p]) < min_var ? abs(nums[i] - nums[p]) : min_var;
//		}
//	}
//	cout << min_var << endl;
//	return 0;
//}