#define TRACE
#include "disjoint_set.hpp"
#include <string>

using namespace zhf_lib;
using namespace std;



int main()
{
	{
		DisjointSet_List<int> dds;
		DisjointSet_ListNode<int> n1(1, dds);
		DisjointSet_ListNode<int> n2(2, dds);
		DisjointSet_ListNode<int> n3(3, dds);
		dds.make_set(n1);
		dds.make_set(n2);
		dds.make_set(n3);
		cout << dds;
		dds.union_set(n1, n2);

		cout << dds;
		dds.union_set(n1, n2);

		dds.union_set(n3, n2);

		cout << dds;
	}
	string s;
	getline(cin, s);
	return 0;
}