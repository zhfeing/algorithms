#include "binarySearchTree.h"
using namespace std;
int Count;
BSTree::BSTree(Vint d)
{
	l = nullptr;
	r = nullptr;
	p = nullptr;
	root = nullptr;
	srand(time(0));
	for (int i = 0; i < d.size(); i++)
	{
		treeInsert(d[i]);
	}
}
void BSTree::inorderTreeWalk(BSTree *x)
{
	if (x != nullptr)
	{
		inorderTreeWalk(x->l);
		cout << x->k << "\t";
		inorderTreeWalk(x->r);
	}
}
void BSTree::setRoot(BSTree *r)
{
	root = r;
}
BSTree *BSTree::treeSuccessor(BSTree *x)
{
	if (x->r != nullptr)
	{
		return treeMin(x->r);
	}
	BSTree *y = x->p;
	while (y != nullptr &&x == y->r)
	{
		x = y;
		y = y->p;
	}
	return y;
}
BSTree *BSTree::treeProcessor(BSTree *x)
{
	if (x->l != nullptr)
	{
		return treeMax(x->l);
	}
	BSTree *y = x->p;
	while (y != nullptr &&x == y->l)
	{
		x = y;
		y = y->p;
	}
	return y;
}
void BSTree::treeInsert(KeyType key)
{
	BSTree *z = new BSTree(key);
	BSTree *x = root;
	BSTree *y = nullptr;
	while (x != nullptr)
	{
		y = x;
		if (key < x->k)
			x = x->l;
		else
			x = x->r;
		Count++;
	}
	z->p = y;
	if (y == nullptr)	//empty tree
	{
		root = z;
	}
	else if (key < y->k)
	{
		y->l = z;
	}
	else
	{
		y->r = z;
	}
}
void BSTree::treeDelete(BSTree *x)
{
	if (x->p != nullptr)
		if (x == x->p->l)//x is left son
		{
			x->p->l = nullptr;
		}
		else//x is right son
		{
			x->p->r = nullptr;
		}
	else
	{
		root = nullptr;
	}
	Delete(x);
}
void BSTree::Delete(BSTree *x)
{
	if (x != nullptr)
	{
		Delete(x->l);
		Delete(x->r);
		delete x;
	}
}
BSTree *BSTree::treeMax(BSTree *x)
{
	if (x != nullptr)
		while (x->r != nullptr)
			x = x->r;
	return x;
}
BSTree *BSTree::treeMin(BSTree *x)
{
	if (x != nullptr)
		while (x->l != nullptr)
			x = x->l;
	return x;
}
BSTree *BSTree::treeSearch(BSTree *x, KeyType key)
{
	while (x != nullptr && key != x->k)
	{
		if (x->k > key)
			x = x->l;
		else
			x = x->r;
	}
	return x;
}
void BSTree::treeNodeDelete(BSTree *x)
{
	if (x == nullptr)
		return;
	else if (x->r == nullptr)//x do not have right son
	{
		treeTransPlant(x->l, x);
	}
	else if (x->l == nullptr)
	{
		treeTransPlant(x->r, x);
	}
	else
	{
		BSTree *y = treeMin(x->r);
		if (y->p != x)
		{
			treeTransPlant(y->r, y);
			y->r = x->r;
			y->r->p = y;
		}
		treeTransPlant(y, x);
		y->l = x->l;
		x->l->p = y;
	}
}
//replace c with x
void BSTree::treeTransPlant(BSTree *x, BSTree *c)
{
	if (c == root)
	{
		root = x;
	}
	else
	{
		if (c->p->l == c)//c is left son
		{
			c->p->l = x;
		}
		else
		{
			c->p->r = x;
		}
		if (x != nullptr)
			x->p = c->p;
	}
}

RedBlackTree::RedBlackTree()
{
	r = nullptr;
	l = nullptr;
	root = nullptr;
	p = nullptr;
	c = Red;
}
RedBlackTree *RedBlackTree::treeSearch(RedBlackTree *x, KeyType key)
{
	while (x != nullptr && key != x->k)
	{
		if (x->k > key)
			x = x->l;
		else
			x = x->r;
	}
	return x;
}

RedBlackTree *RedBlackTree::successor(RedBlackTree *x)
{
	if (x->r != nullptr)
	{
		return treeMin(x->r);
	}
	RedBlackTree *y = x->p;
	while (y != nullptr &&x == y->r)
	{
		x = y;
		y = y->p;
	}
	return y;
}
RedBlackTree *RedBlackTree::prosuccessor(RedBlackTree *x)
{
	if (x->l != nullptr)
	{
		return treeMax(x->l);
	}
	RedBlackTree *y = x->p;
	while (y != nullptr &&x == y->l)
	{
		x = y;
		y = y->p;
	}
	return y;
}
void RedBlackTree::treeInsertion(KeyType key)
{
	RedBlackTree *z = new RedBlackTree;
	RedBlackTree *x = root;
	RedBlackTree *y = nullptr;
	while (x != nullptr)
	{
		y = x;
		if (key < x->k)
			x = x->l;
		else
			x = x->r;
		Count++;
	}
	z->p = y;
	if (y == nullptr)	//empty tree
	{
		root = z;
	}
	else if (key < y->k)
	{
		y->l = z;
	}
	else
	{
		y->r = z;
	}
	RBtreeInsertFixup(z);
}
void RedBlackTree::treeRotate(RedBlackTree *x, TreeRotation rotation)
{
	if (rotation == Left)
	{
		RedBlackTree *y = x->r;
		if (y == nullptr)
		{
			cerr << "error! in left rotation" << endl;
			exit(EXIT_FAILURE);
		}
		x->r = y->l;
		if (y->l != nullptr)
		{
			y->l->p = x;
		}
		y->p = x->p;
		if (x->p == nullptr)
		{
			root = y;
		}
		else if (x == x->p->l)
		{
			x->p->l = y;
		}
		else
		{
			x->p->r = y;
		}
		y->l = x;
		x->p = y;
	}
	else
	{
		RedBlackTree *y = x->l;
		if (y == nullptr)
		{
			cerr << "error! in right rotation" << endl;
			exit(EXIT_FAILURE);
		}
		x->l = y->r;
		if (y->r != nullptr)
		{
			y->r->p = x;
		}
		y->p = x->p;
		if (x->p == nullptr)
		{
			root = y;
		}
		else if (x == x->p->r)
		{
			x->p->r = y;
		}
		else
		{
			x->p->l = y;
		}
		y->r = x;
		x->p = y;
	}
}
RedBlackTree *RedBlackTree::treeMax(RedBlackTree *x)
{
	if (x != nullptr)
		while (x->r != nullptr)
			x = x->r;
	return x;
}
RedBlackTree *RedBlackTree::treeMin(RedBlackTree *x)
{
	if (x != nullptr)
		while (x->l != nullptr)
			x = x->l;
	return x;
}
void RedBlackTree::inorderTreeWalk(RedBlackTree *x)
{
	if (x != nullptr)
	{
		inorderTreeWalk(x->l);
		cout << x->k << "\t";
		inorderTreeWalk(x->r);
	}
}
void RedBlackTree::RBtreeInsertFixup(RedBlackTree *z)
{
	
}