#include "project.h"
int main()
{
	srand((unsigned)time(0));
	SkipList<int> T;
	for (int i = 0; i < 1000; i++)
	{
		T.insert(2*rand() + 1);
	}
	T.print();
	try
	{
		while (true)
		{
			int aaa;
			cout << "enter \"i\" to insert, \"d\"to delete" << endl;
			string s;
			cin >> s;
			if (!strcmp(s.c_str(), "i"))	//enter insert
			{
				cout << "enter number" << endl;
				cin >> aaa;
				T.insert(aaa);
				cout << endl;
				T.print();
			}
			else if (!strcmp(s.c_str(), "d"))
			{
				cout << "enter number" << endl;
				cin >> aaa;
				T.deleteNode(T.search(aaa));
				cout << endl;
				T.print();
			}
			else
			{
				cout << "try again" << endl;
			}
		}
	}
	catch (SkipList<int>::Bad_Key)
	{
		cerr << "error key" << endl;
	}
	catch (SkipList<int>::Bad_Node)
	{
		cerr << "number not find" << endl;
	}
	return 0;
}