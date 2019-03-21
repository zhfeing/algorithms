////2018研究生上机测试
//#include <iostream>
//#include <algorithm>
//#include <vector>
//#include <string>
//
//using namespace std;
//
//bool check_like(vector<int> &num)
//{
//	int length = num.size();
//	for (int i = 0; i < length / 2; i++)
//	{
//		if (num[i] != num[length - i - 1])
//		{
//			return false;
//		}
//	}
//	int sum = 0;
//	for (auto iter = num.begin(); iter != num.end(); iter++)
//	{
//		sum += *iter;
//	}
//	// check length
//	length = 1;
//	int temp = sum;
//	while ((temp /= 10) != 0)
//	{
//		length++;
//	}
//	for (int i = 0; i < length / 2; i++)
//	{
//		int lsb = int(sum / pow(10, i)) % 10;
//		int msb = sum / pow(10, length - 1 - i);
//		if (lsb != msb)
//		{
//			return false;
//		}
//	}
//	return true;
//}
//
//int main()
//{
//	int k;
//	cin >> k;
//	vector<string> num_string(k);
//	vector<vector<int>> nums(k);
//	for (int i = 0; i < k; i++)
//	{
//		cin >> num_string[i];
//		int len = num_string[i].length();
//		nums[i].resize(len);
//		for (int j = 0; j < len; j++)
//		{
//			nums[i][j] = num_string[i][j] - '0';
//		}
//	}
//
//	int number_of_like = 0;
//	for (int i = 0; i < k; i++)
//	{
//		if (check_like(nums[i]))
//		{
//			number_of_like++;
//		}
//	}
//	cout << number_of_like;
//	//system("pause");
//	return 0;
//}