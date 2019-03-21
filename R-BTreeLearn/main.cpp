#include "project.h"
using namespace std;
using namespace trees;
int main()
{
	RBtree<int> aa;
	srand(time(0));
	for (int i = 0; i < 10000; i++)
	{
		aa.treeInsert(rand() % 10);
	}
	aa.inorderTreeWalk(aa.root());
	getchar();
	return 0;
}
