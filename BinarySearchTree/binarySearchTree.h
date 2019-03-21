#pragma once
#ifndef _INC_BINARY_SEARCH_TREE
#define _INC_BINARY_SEARCH_TREE

#include <iostream>
#include <ctime>
#include <vector>
#include <cstdlib>
using std::vector;
typedef vector<int> Vint;
extern int Count;
class BSTree
{
public:
	typedef int KeyType;

	BSTree(BSTree *left, BSTree *right, BSTree *parent, KeyType key)
	{
		l = left;
		r = right;
		p = parent;
		k = key;
		root = nullptr;
	}
	BSTree(KeyType key)
	{
		k = key;
		l = nullptr;
		r = nullptr;
		p = nullptr;
		root = nullptr;
	}
	BSTree()
	{
		l = nullptr;
		r = nullptr;
		p = nullptr;
		root = nullptr;
	}
	BSTree(Vint);
	BSTree *left()
	{
		return l;
	}
	BSTree *right()
	{
		return r;
	}
	BSTree *parent()
	{
		return p;
	}
	KeyType key()
	{
		return k;
	}
	void left(BSTree *l)
	{
		this->l = l;
	}
	void right(BSTree *r)
	{
		this->r = r;
	}
	void parent(BSTree *p)
	{
		this->p = p;
	}
	void key(KeyType k)
	{
		this->k = k;
	}

	void inorderTreeWalk(BSTree *);
	void setRoot(BSTree *);
	BSTree *getRoot()
	{
		return root;
	}
	void treeInsert(KeyType);
	void treeDelete(BSTree *);
	void treeNodeDelete(BSTree *);
	BSTree *treeMax(BSTree *);
	BSTree *treeMin(BSTree *);
	BSTree *treeSearch(BSTree *x, KeyType key);
	//find the successor
	BSTree *treeSuccessor(BSTree *x);
	//find the processor
	BSTree *treeProcessor(BSTree *x);
private:
	BSTree *l;
	BSTree *r;
	BSTree *p;
	KeyType k;
	BSTree *root;
	void Delete(BSTree *);
	//replace c with x
	void treeTransPlant(BSTree *x, BSTree *c);
};

class RedBlackTree
{
public:
	typedef int KeyType;
	enum Colour
	{
		Red, Black
	};
	enum TreeRotation
	{
		Right, Left
	};
	RedBlackTree();
	RedBlackTree *treeSearch(RedBlackTree *, KeyType);
	void inorderTreeWalk(RedBlackTree *);
	Colour treeColour()
	{
		return c;
	}
	RedBlackTree *left()
	{
		return l;
	}
	void left(RedBlackTree *left)
	{
		l = left;
	}
	RedBlackTree *right()
	{
		return r;
	}
	void right(RedBlackTree *right)
	{
		r = right;
	}
	RedBlackTree *parent()
	{
		return p;
	}
	void parent(RedBlackTree *p)
	{
		this->p = p;
	}
	KeyType key()
	{
		return k;
	}
	void key(KeyType k)
	{
		this->k = k;
	}
	RedBlackTree *successor(RedBlackTree *);
	RedBlackTree *prosuccessor(RedBlackTree *);
	RedBlackTree *getRoot()
	{
		return root;
	}
	void setRoot(RedBlackTree *root)
	{
		this->root = root;
	}
	RedBlackTree *treeMax(RedBlackTree *);
	RedBlackTree *treeMin(RedBlackTree *);
	void treeInsertion(KeyType);
	void treeRotate(RedBlackTree *, TreeRotation);
	//replace c with x
	//void treeTransPlant(RedBlackTree *x, RedBlackTree *c);
private:
	KeyType k;
	Colour c;
	RedBlackTree *l;
	RedBlackTree *r;
	RedBlackTree *p;
	RedBlackTree *root;
	void RBtreeInsertFixup(RedBlackTree *);
};
#endif // !_INC_BINARY_SEARCH_TREE
