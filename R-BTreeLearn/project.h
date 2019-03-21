#ifndef __INC_PROJECT
#define __INC_PROJECT

#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <string>
#include <cstdlib>
#include <ctime>

namespace trees
{
	template<class Key> class TreeNode;
	template<class Key> class BinaryTree; 
	template<class Key> class BinarySearchTree;
	template<class Key> class RBtree;
	
	///class TreeNode
	//the node data structure for a binary tree
	template<class Key> class TreeNode
	{
	public:
		enum Color
		{
			Red, Black
		};
		TreeNode();
		TreeNode(Key key, TreeNode *left = nullptr,
			TreeNode *right = nullptr, TreeNode *parent = nullptr);
		TreeNode(Key key, Color color, TreeNode *left = nullptr,
			TreeNode *right = nullptr, TreeNode *parent = nullptr);
		TreeNode *left();
		TreeNode *right();
		TreeNode *parent();
		Key key();
		Color color();
		//NIL is a special one for root do not create another one
		static TreeNode *const NIL;

		friend BinaryTree<Key>;
		friend BinarySearchTree<Key>;
		friend RBtree<Key>;

		class Bad_Color{ };
	protected:
		TreeNode *l, *r, *p;
		Key k;
		//propertities
		Color col;
	};
	
	///class BinatyTree
	template<class Key> class BinaryTree
	{
	public:
		BinaryTree();
		BinaryTree(const TreeNode<Key> &);
		virtual ~BinaryTree();
		TreeNode<Key> *root();

		class Bad_Operator
		{
		};
		class Bad_pointer
		{
		};
	protected:
		TreeNode<Key> *TreeRoot;
	private:
		///do not use folowing function for safe
		BinaryTree(const BinaryTree &)
		{
			throw Bad_Operator();
		}
		BinaryTree operator=(BinaryTree)
		{
			throw Bad_Operator();
		}
	};

	template<class Key>
	std::ostream &operator<<(std::ostream &, TreeNode<Key>&);
	template<class Key>
	std::ostream &operator<<(std::ostream &, TreeNode<Key>*);

	///class BinarySearchTree
	//left <= this < right
	template<class Key> class BinarySearchTree
		:public BinaryTree<Key>
	{
	public:
		BinarySearchTree();
		BinarySearchTree(const TreeNode<Key> &);
		virtual ~BinarySearchTree();
		virtual void inorderTreeWalk(const TreeNode<Key> *);
		
		TreeNode<Key> *treeSearch(Key, TreeNode<Key> *);
		TreeNode<Key> *treeMin(TreeNode<Key> *);
		TreeNode<Key> *treeMax(TreeNode<Key> *);
		TreeNode<Key> *treeSuccessor(TreeNode<Key> *);
		TreeNode<Key> *treeProsuccessor(TreeNode<Key> *);
		virtual void treeInsert(const Key y);
		virtual void treeDelete(TreeNode<Key> *);
		virtual void treeNodeDelete(TreeNode<Key> *);
	private:
		void _delete(TreeNode<Key> *);
		void transPlant(TreeNode<Key>* u, TreeNode<Key> *v);

		///do not use folowing function for safe
		BinarySearchTree(const BinarySearchTree &)
		{
			throw Bad_Operator();
		}
		BinarySearchTree operator=(BinarySearchTree)
		{
			throw Bad_Operator();
		}
	};
	///class R-Btree
	//left < this < right
	//! do not allow same key
	template<class Key> class RBtree
		: public BinarySearchTree<Key>
	{
	public:
		RBtree();
		RBtree(const TreeNode<Key> &);
		virtual ~RBtree();
		virtual void inorderTreeWalk(const TreeNode<Key> *);
		virtual void treeInsert(const Key y);
		virtual void treeNodeDelete(TreeNode<Key> *);
	private:
		void leftRotate(TreeNode<Key> *);
		void rightRotate(TreeNode<Key> *);
		void RB_InsertFixup(TreeNode<Key> *);
		///do not use folowing function for safe
		RBtree(const RBtree &)
		{
			throw Bad_Operator();
		}
		RBtree operator=(RBtree)
		{
			throw Bad_Operator();
		}
	};
}

namespace trees
{
	///class TreeNode
	template<class Key>
	TreeNode<Key>::TreeNode()
	{
		l = nullptr;
		r = nullptr;
		p = nullptr;
		k = Key();
		col = Black;
	}
	//TreeNode(Key key, TreeNode *left, TreeNode *right, TreeNode *parent)
	template<class Key>
	TreeNode<Key>::TreeNode(Key key, TreeNode *left/* = nullptr*/,
		TreeNode *right/* = nullptr*/, TreeNode *parent/* = nullptr*/)
		:l(left), r(right), p(parent), k(key), col(Black)
	{
	}
	template<class Key>
	TreeNode<Key>::TreeNode(Key key, Color color, TreeNode *left = nullptr,
		TreeNode *right = nullptr, TreeNode *parent = nullptr)
		: l(left), r(right), p(parent), k(key), col(color)
	{
	}
	template<class Key>
	TreeNode<Key> *TreeNode<Key>::left()
	{
		return l;
	}
	template<class Key>
	TreeNode<Key> *TreeNode<Key>::right()
	{
		return r;
	}
	template<class Key>
	TreeNode<Key> *TreeNode<Key>::parent()
	{
		return p;
	}
	template<class Key>
	Key TreeNode<Key>::key()
	{
		return k;
	}
	template<class Key>
	typename TreeNode<Key>::Color TreeNode<Key>::color()
	{
		return col;
	}

	template<class Key>
	TreeNode<Key> *const TreeNode<Key>::NIL = new TreeNode;

	template<class Key>
	std::ostream &operator<<(std::ostream &out, TreeNode<Key> &node)
	{
		out << node.key();
		return out;
	}
	template<class Key>
	std::ostream &operator<<(std::ostream &out, TreeNode<Key> *node)
	{
		out << (*node).key();
		return out;
	}
	
	///class BinaryTree
	template<class Key>
	BinaryTree<Key>::BinaryTree()
		:TreeRoot(TreeNode<Key>::NIL)
	{
	}
	template<class Key>
	BinaryTree<Key>::BinaryTree(const TreeNode<Key>& root)
	{
		if (&root != TreeNode<Key>::NIL)
			TreeRoot = new TreeNode<Key>(root);
		else
			TreeRoot = TreeNode<Key>::NIL;
	}
	template<class Key>
	BinaryTree<Key>::~BinaryTree()
	{
		if (TreeRoot != TreeNode<Key>::NIL)
			delete TreeRoot;
	}
	template<class Key>
	TreeNode<Key> *BinaryTree<Key>::root()
	{
		return TreeRoot;
	}
}
///for the specific data structure
namespace trees
{
	///class BinarySearchTree
	template<class Key>
	BinarySearchTree<Key>::BinarySearchTree()		
	{
		TreeRoot = TreeNode<Key>::NIL;
	}
	template<class Key>
	BinarySearchTree<Key>::BinarySearchTree(const TreeNode<Key>& root)
	{
		if (&root != TreeNode<Key>::NIL)
			TreeRoot = new TreeNode<Key>
			(root.k, TreeNode<Key>::NIL, TreeNode<Key>::NIL, TreeNode<Key>::NIL);
		else
			TreeRoot = TreeNode<Key>::NIL;
	}
	
	template<class Key>
	inline BinarySearchTree<Key>::~BinarySearchTree()
	{
		treeDelete(TreeRoot);
	}
	template<class Key>
	void BinarySearchTree<Key>::inorderTreeWalk(const TreeNode<Key> *x)
	{
		if (x != TreeNode<Key>::NIL)
		{
			inorderTreeWalk(x->l);
			cout << x->k << endl;
			inorderTreeWalk(x->r);
		}
	}
	template<class Key>
	TreeNode<Key> *BinarySearchTree<Key>::treeSearch(Key key, TreeNode<Key> *x)
	{
		while (x != TreeNode<Key>::NIL)
		{
			if (key < x->k)
			{
				x = x->l;
			}
			else if (key > x->k)
			{
				x = x->r;
			}
			else
			{
				break;
			}
		}
		return x;
	}
	template<class Key>
	TreeNode<Key> *BinarySearchTree<Key>::treeMin(TreeNode<Key> *x)
	{
		TreeNode<Key> *y = x;
		while (x != TreeNode<Key>::NIL)
		{
			y = x;
			x = x->l;
		}
		return y;
	}
	template<class Key>
	TreeNode<Key> *BinarySearchTree<Key>::treeMax(TreeNode<Key> *x)
	{
		TreeNode<Key> *y = x;
		while (x != TreeNode<Key>::NIL)
		{
			y = x;
			x = x->r;
		}
		return y;
	}
	template<class Key>
	TreeNode<Key> *BinarySearchTree<Key>::treeSuccessor(TreeNode<Key> *x)
	{
		if (x != TreeNode<Key>::NIL)
		{
			if(x->r != TreeNode<Key>::NIL)
				return treeMin(x->r);
			else
			{
				TreeNode<Key> *y = x->p;
				while (y != TreeNode<Key>::NIL && x == y->r)
				{
					x = y;
					y = y->p;
				}
			}
		}
		else
		{
			throw Bad_pointer();
		}
	}
	template<class Key>
	TreeNode<Key> *BinarySearchTree<Key>::treeProsuccessor(TreeNode<Key> *x)
	{
		if (x != TreeNode<Key>::NIL)
		{
			if (x->l != TreeNode<Key>::NIL)
				return treeMax(x->l);
			else
			{
				TreeNode<Key> *y = x->p;
				while (y != TreeNode<Key>::NIL && x == y->l)
				{
					x = y;
					y = y->p;
				}
			return y;
			}
		}
		else
		{
			throw Bad_pointer();
		}
	}
	template<class Key>
	void BinarySearchTree<Key>::treeInsert(const Key k)
	{
		if (TreeRoot == TreeNode<Key>::NIL)	//empty tree
		{
			TreeRoot = new TreeNode<Key>
				(k, TreeNode<Key>::NIL, TreeNode<Key>::NIL, TreeNode<Key>::NIL);
		}
		else
		{
			TreeNode<Key> *x = TreeRoot;
			TreeNode<Key> *y = x;
			while (x != TreeNode<Key>::NIL)
			{
				y = x;
				if (x->k >= k)	//insert to the left of y
				{
					x = x->l;
				}
				else
				{
					x = x->r;
				}
			}
			TreeNode<Key> *n = new TreeNode<Key>(k, TreeNode<Key>::NIL, TreeNode<Key>::NIL, y);
			if (y->k >= k)	//insert to the left of y
			{
				y->l = n;
			}
			else
			{
				y->r = n;
			}			
		}
	}
	template<class Key>
	void BinarySearchTree<Key>::_delete(TreeNode<Key> *x)
	{
		if (x != TreeNode<Key>::NIL)
		{
			treeDelete(x->left());
			treeDelete(x->right());
			delete x;
		}
	}
	template<class Key>
	void BinarySearchTree<Key>::transPlant(TreeNode<Key>* u, TreeNode<Key>* v)
	{
		if (u->p == TreeNode<Key>::NIL)
		{
			TreeRoot = v;
		}
		else if (u == u->p->l)
		{
			u->p->l = v;
		}
		else
		{
			u->p->p->r = v;
		}
		if (v != TreeNode<Key>::NIL)
		{
			v->p = u->p;
		}
	}
	template<class Key>
	void BinarySearchTree<Key>::treeDelete(TreeNode<Key> *x)
	{
		if (x != TreeNode<Key>::NIL)
		{
			if (x->p != TreeNode<Key>::NIL)	//x is not root
			{
				if (x == x->p->l)
					x->p->l = TreeNode<Key>::NIL;
				else
					x->p->r = TreeNode<Key>::NIL;
				_delete(x);
			}
			else
			{
				delete x;
				TreeRoot = TreeNode<Key>::NIL;
			}
		}
	}
	template<class Key>
	void BinarySearchTree<Key>::treeNodeDelete(TreeNode<Key>* z)
	{
		if (z->l == TreeNode<Key>::NIL)
		{
			transPlant(z, z->r);
		}
		else if (z->r == TreeNode<Key>::NIL)
		{
			transPlant(z, z->l);
		}
		else
		{
			TreeNode<Key> *y = treeMin(z->r);
			if (y->p != z)
			{
				transPlant(y, y->r);
				y->r = z->r;
				y->r->p = y;
			}
			transPlant(z, y);
			y->l = z->l;
			y->l->p = y;
		}
	}
}
///for R-BTree
namespace trees
{
	template<class Key>
	RBtree<Key>::RBtree()
	{
		TreeRoot = TreeNode<Key>::NIL;
	}
	template<class Key>
	RBtree<Key>::RBtree(const TreeNode<Key> &root)
	{
		if (&root != TreeNode<Key>::NIL)
		{
			this->TreeRoot = new TreeNode<Key>(root.k, TreeNode<Key>::Black, 
				TreeNode<Key>::NIL, TreeNode<Key>::NIL, TreeNode<Key>::NIL);
		}
		else
			TreeRoot = TreeNode<Key>::NIL;
	}

	template<class Key>
	RBtree<Key>::~RBtree()
	{
		treeDelete(TreeRoot);
	}
	template<class Key>
	void RBtree<Key>::inorderTreeWalk(const TreeNode<Key>*x)
	{
		if (x != TreeNode<Key>::NIL)
		{
			inorderTreeWalk(x->l);
			switch (x->col)
			{
			case TreeNode<Key>::Black:
				cout << x->k << " Black" << endl;
				break;
			case TreeNode<Key>::Red:
				cout << x->k << " Red" << endl;
				break;
			default:
				throw (TreeNode<Key>::Bad_Color());
			}
			inorderTreeWalk(x->r);
		}
	}
	template<class Key>
	void RBtree<Key>::treeInsert(const Key k)
	{
		TreeNode<Key> *y = TreeNode<Key>::NIL;
		TreeNode<Key> *x = TreeRoot;
		while (x != TreeNode<Key>::NIL)
		{
			y = x;
			if (k < x->k)
			{
				x = x->l;
			}
			else
			{
				x = x->r;
			}
		}
		TreeNode<Key> *z = new TreeNode<Key>(k, TreeNode<Key>::Red, 
			TreeNode<Key>::NIL, TreeNode<Key>::NIL, y);
		if (y == TreeNode<Key>::NIL)
		{
			TreeRoot = z;
		}
		else if (z->k < y->k)
		{
			y->l = z;
		}
		else
		{
			y->r = z;
		}
		RB_InsertFixup(z);
	}
	template<class Key>
	void RBtree<Key>::treeNodeDelete(TreeNode<Key> *x)
	{

	}
	template<class Key>
	void RBtree<Key>::leftRotate(TreeNode<Key> *x)
	{
		TreeNode<Key> *y = x->r;
		x->r = y->l;
		if (y->l != TreeNode<Key>::NIL)
		{
			y->l->p = x;
		}
		y->p = x->p;
		if (x->p == TreeNode<Key>::NIL)
		{
			TreeRoot = y;
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
	template<class Key>
	void RBtree<Key>::rightRotate(TreeNode<Key> *x)
	{
		TreeNode<Key> *y = x->l;
		x->l = y->r;
		if (y->r != TreeNode<Key>::NIL)
		{
			y->r->p = x;
		}
		y->p = x->p;
		if (x->p == TreeNode<Key>::NIL)
		{
			TreeRoot = y;
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
	template<class Key>
	void RBtree<Key>::RB_InsertFixup(TreeNode<Key> *z)
	{
		if (z == TreeRoot)
		{
			z->col = TreeNode<Key>::Black;
			return;
		}
		else if (z->p == TreeRoot)
		{
			return;
		}
		while (z->p->col == TreeNode<Key>::Red)
		{
			if (z->p == z->p->p->l)
			{
				TreeNode<Key> *y = z->p->p->r;
				if (y->col == TreeNode<Key>::Red)
				{
					z->p->col = TreeNode<Key>::Black;
					y->col = TreeNode<Key>::Black;
					z->p->p->col = TreeNode<Key>::Red;
					z = z->p->p;
				}
				else if (z == z->p->r)
				{
					z = z->p;
					leftRotate(z);
				}
				else
				{
					z->p->col = TreeNode<Key>::Black;
					z->p->p->col = TreeNode<Key>::Red;
					rightRotate(z->p->p);
				}
			}
			else
			{
				TreeNode<Key> *y = z->p->p->l;
				if (y->col == TreeNode<Key>::Red)
				{
					z->p->col = TreeNode<Key>::Black;
					y->col = TreeNode<Key>::Black;
					z->p->p->col = TreeNode<Key>::Red;
					z = z->p->p;
				}
				else if (z == z->p->l)
				{
					z = z->p;
					rightRotate(z);
				}
				else
				{
					z->p->col = TreeNode<Key>::Black;
					z->p->p->col = TreeNode<Key>::Red;
					leftRotate(z->p->p);
				}
			}
		}
		TreeRoot->col = TreeNode<Key>::Black;
	}
}
#endif // !__INC_PROJECT
