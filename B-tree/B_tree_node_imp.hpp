#ifndef __INC_B_TREE_NODE_IMP_HPP
#define __INC_B_TREE_NODE_IMP_HPP

#include <list>
#include <iostream>
#include <memory>
#include <limits>

#include "B_tree_node.hpp"

#ifndef _STD
#define _STD std::
#endif // !_STD


#ifndef _ZHF_LIN_BEGIN
#define _ZHF_LIB_BEGIN namespace zhf_lib{
#endif // !_ZHF_LIN_BEGIN

#ifndef _END_ZHF_LIB
#define _END_ZHF_LIB }
#endif // !_END_ZHF_LIB


// beigin zhf_lib
_ZHF_LIB_BEGIN

// class BTreeNode
template <typename _Key, typename _Val>
class BTreeNode
{
public:
	BTreeNode();
	virtual ~BTreeNode();
	virtual unsigned get_id() const;
public:

	class Bad_Allocate{ };
	class Bad_InvalidData{ };

	size_t _n;					// number of keys
	bool _valid;				// data valid
	bool _leaf;
	_STD list<_Key> _keys;		// keys
	_STD list<pBTreeNode<_Key, _Val>> _c;	// childs
	_STD list<_Val> _vals;		// satelite data
private:
	unsigned _id;
	// create id for each node;
	unsigned create_id() const;
	// copy invalid
	BTreeNode(const BTreeNode<_Key, _Val> &);
	BTreeNode &operator=(const BTreeNode &);
};


template <typename _Key, typename _Val>
BTreeNode<_Key, _Val>::BTreeNode()
	:_n(0), _id(create_id()), _valid(false)
{
	_STD cout << "BTreeNode construction\tcreate node: " << _id << _STD endl;
}

template <typename _Key, typename _Val>
BTreeNode<_Key, _Val>::~BTreeNode()
{
	_STD cout << "delete node: " << _id << _STD endl;
}

template <typename _Key, typename _Val>
unsigned BTreeNode<_Key, _Val>::create_id() const
{
	static unsigned id = 0;
	if (id == _STD numeric_limits<unsigned>::max())	// cannot create more objects
	{
		throw (Bad_Allocate());
	}
	return id++;
}

template <typename _Key, typename _Val>
unsigned BTreeNode<_Key, _Val>::get_id() const
{
	return _id;
}


template <typename _Key, typename _Val>
class BTreeNode_Disk : public BTreeNode<_Key, _Val>
{
public:
	explicit BTreeNode_Disk(const pBTreeNode<_Key, _Val>&);
	virtual ~BTreeNode_Disk();
	virtual unsigned get_id() const;
private:
	explicit BTreeNode_Disk(const BTreeNode_Disk &);
	BTreeNode_Disk &operator=(const BTreeNode_Disk &);
private:
	unsigned _id;
};

template <typename _Key, typename _Val>
BTreeNode_Disk<_Key, _Val>::BTreeNode_Disk(const pBTreeNode<_Key, _Val> &p)
	: _id(p->get_id())
{
	_STD cout << "BTreeNode_Disk construction" << _STD endl;
	if (!p->_valid)
	{
		throw typename BTreeNode<_Key, _Val>::Bad_InvalidData();
	}
	this->_n = p->_n;
	this->_valid = true;
	this->_keys = p->_keys;
	this->_c = p->_c;
	this->_vals = p->_vals;
}

template <typename _Key, typename _Val>
BTreeNode_Disk<_Key, _Val>::~BTreeNode_Disk()
{
	_STD cout << "delete disk node id_base: " << BTreeNode<_Key, _Val>::get_id() 
		<< " new id: " << get_id() << _STD endl;
}

template <typename _Key, typename _Val>
unsigned BTreeNode_Disk<_Key, _Val>::get_id() const
{
	return _id;
}

_END_ZHF_LIB	// zhf_lib

#endif