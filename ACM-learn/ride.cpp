///*
//PROG: ride
//ID: zhf66691
//LANG: C++
//*/
//#include <iostream>
//#include <fstream>
//#include <string>
//
//using namespace std;
//
//int main()
//{
//	ofstream fout("ride.out");
//	ifstream fin("ride.in");
//	string s1, s2;
//	fin >> s1;
//	fin >> s2;
//
//	int data1 = 1;
//	for (int i = 0; s1[i] != '\0'; i++)
//	{
//		data1 *= int(s1[i] - 'A' + 1) % 47;
// 		data1 %= 47;
//	}
//	int data2 = 1;
//	for (int i = 0; s2[i] != '\0'; i++)
//	{
//		data2 *= int(s2[i] - 'A' + 1) % 47;
//		data2 %= 47;
//	}
//	if (data1 == data2)
//	{
//		fout << "GO" << endl;
//	}
//	else
//	{
//		fout << "STAY" << endl;
//	}
//	 getchar();
//	return 0;
//}