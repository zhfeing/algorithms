///*2072*/
//#include <iostream>
//#include <fstream>
//#include <vector>
//#include <string>
//#include <algorithm>
//
//using namespace std;
//
//vector<string> Table;
//
//int string_in_table(const string &s)
//{
//	for (int i = 0; i < Table.size(); i++)
//	{
//		if (s == Table[i])
//			return i;
//	}
//	return -1;
//}
//
//
//int main()
//{
//	string line;
//	while (getline(cin, line))
//	{
//		bool new_word = true;
//		bool word_checked = true;
//		bool done = false;
//		string word;
//		if (line == "#")
//			break;
//		for (string::iterator iter = line.begin(); iter != line.end(); iter++)
//		{
//			if (*iter == '#')
//			{
//				done = true;
//				break;
//			}
//			if (*iter == ' ')
//			{
//				new_word = true;
//				if (!word_checked)
//				{
//					word_checked = true;
//					int code = string_in_table(word);
//					if (code == -1)
//					{
//						Table.push_back(word);
//					}
//				}
//				word.resize(0);
//			}
//			else
//			{
//				word_checked = false;
//				if (new_word)
//				{
//					new_word = false;
//				}
//				word.push_back(*iter);
//			}
//		}
//		if (word.size() != 0)
//		{
//			int code = string_in_table(word);
//			if (code == -1)
//			{
//				Table.push_back(word);
//			}
//		}
//		cout << Table.size() << endl;
//		Table.resize(0);
//		if (done)
//		{
//			break;
//		}
//	}
//	//getchar();
//	//getchar();
//	//getchar();
//	//getchar();
//	//getchar();
//	return 0;
//}
