#ifndef __INC_B_TREE_HPP
#define __INC_B_TREE_HPP

#include <list>

#include "B_tree_node.hpp"
#include "disk.hpp"

#ifndef _STD
#define _STD std::
#endif // !_STD

#ifndef _ZHF_LIN_BEGIN
#define _ZHF_LIB_BEGIN namespace zhf_lib{
#endif // !_ZHF_LIN_BEGIN

#ifndef _END_ZHF_LIB
#define _END_ZHF_LIB }
#endif // !_END_ZHF_LIB

_ZHF_LIB_BEGIN // begin namespace zhf_lib

// class BTree
template <typename _Key, typename _Val>
class BTree
{
public:
	BTree(size_t t);
	_Val &find(const _Key &key);
	void insert(const _Key &key, const _Val &val);
	void erase(const _Key &key);

private:
	// copy forbidden
	explicit BTree(const BTree&);
	BTree &operator=(const BTree&);

	// initial function
	pBTreeNode<_Key, _Val> make_root();
	// auxiliary function
	void split_chile(pBTreeNode<_Key, _Val> &, size_t);
	void insert_non_full(pBTreeNode<_Key, _Val> &, const _Key &, const _Val &);

private:
	// the min size of child
	size_t _t;
	const size_t _MaxChildSize;
	// the initial order depends on the order of declaration 
	pBTreeNode<_Key, _Val> _root;
	DiskSimulator<_Key, _Val> _disk;	// _disk initialization depends on _root
};


template <typename _Key, typename _Val>
BTree<_Key, _Val>::BTree(size_t t)
	:_root(make_root()), _disk(_root), _t(t), _MaxChildSize(2*_t - 1)
{

}

template <typename _Key, typename _Val>
void BTree<_Key, _Val>::insert(const _Key &key, const _Val &val)
{
	pBTreeNode<_Key, _Val> r = _root;
	if(r->_n == _MaxChildSize)
	{

	}
	else
	{
		insert_non_full(r, key, val)
	}
}

template <typename _Key, typename _Val>
void BTree<_Key, _Val>::erase(const _Key &key)
{
	
}

template <typename _Key, typename _Val>
_Val &BTree<_Key, _Val>::find(const _Key &key)
{

}

template <typename _Key, typename _Val>
pBTreeNode<_Key, _Val> BTree<_Key, _Val>::make_root()
{
	pBTreeNode<_Key, _Val> p0(new BTreeNode<_Key, _Val>());
	p0->_valid = true;
	p0->_leaf = true;
	return p0;
}





template <typename _Key, typename _Val>
void BTree<_Key, _Val>::split_chile(pBTreeNode<_Key, _Val> &x, size_t index)
{
	// typename _STD list<pBTreeNode<_Val, _Key>>::iterator y = x->_c.begin();
	// for (int i = 0; i < index; i++)
	// {
	// 	y++;
	// }
	
	
	// pBTreeNode<_Key, _Val> z = new BTreeNode<_Key, _Val>();
	// z->_valid = true;
	// z->_leaf = y->_leaf;
}

template <typename _Key, typename _Val>
void BTree<_Key, _Val>::insert_non_full(pBTreeNode<_Key, _Val> &x, 
										const _Key &key, const _Val &val)
{

}

_END_ZHF_LIB

#endif
