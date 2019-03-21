#include"binarySearchTree.h"
using namespace std;
int main()
{
	RedBlackTree t1, t2, t3;
	t1.left(&t2);
	t1.setRoot(&t1);
	t1.right(nullptr);
	t1.parent(nullptr);
	t1.key(3);

	t2.parent(&t1);
	t2.left(nullptr);
	t2.right(&t3);
	t2.key(1);
	t2.setRoot(&t1);

	t3.key(2);
	t3.left(nullptr);
	t3.right(nullptr);
	t3.parent(&t2);
	t3.setRoot(&t1);

	t1.inorderTreeWalk(&t1);
	t1.treeRotate(&t1, RedBlackTree::Right);
	cout << endl;
	t1.inorderTreeWalk(t1.getRoot());
	getchar(); getchar();
	return 0;
}