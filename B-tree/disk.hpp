#ifndef __INC_DISK_HPP
#define __INC_DISK_HPP

#include <iostream>
#include <memory>
#include <map>
#include <thread>

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

_ZHF_LIB_BEGIN // begin namespace zhf_lib


// class DiskSimlator
template <typename _Key, typename _Val>
class DiskSimulator
{
	using _MyMap = _STD map<unsigned, pBTreeNode_Disk<_Key, _Val>>;
	using _MyPair = _STD pair<unsigned, pBTreeNode_Disk<_Key, _Val>>;
public:
	class Bad_DataInvalid
	{
	};
	class Bad_NodeNotFound
	{
	};

public:
	DiskSimulator(const pBTreeNode<_Key, _Val> &root);
	~DiskSimulator();

	void disk_write(pBTreeNode<_Key, _Val> &p0);
	void disk_read(pBTreeNode<_Key, _Val> &x);

private:
	inline void disk_write_delay() const;
	inline void disk_read_delay() const;
	void sleep(unsigned n_ms) const;
	inline void check_node(const pBTreeNode<_Key, _Val> &p) const;
private:
	_MyMap _tree_node_index;
};


template <typename _Key, typename _Val>
DiskSimulator<_Key, _Val>::DiskSimulator(const pBTreeNode<_Key, _Val> &root)
{
	check_node(root);
	pBTreeNode_Disk<_Key, _Val> p(new BTreeNode_Disk<_Key, _Val>(root));
	_tree_node_index.insert(_MyPair(root->get_id(), p));
	_STD cout << "create root on the disk" << _STD endl;
}

template <typename _Key, typename _Val>
DiskSimulator<_Key, _Val>::~DiskSimulator()
{

}

template <typename _Key, typename _Val>
void DiskSimulator<_Key, _Val>::disk_write(pBTreeNode<_Key, _Val> &p)
{
	check_node(p);
	// simulate disk write delay time
	disk_write_delay();
	// search p0->_n
	typename _MyMap::iterator it = _tree_node_index.find(p->get_id());
	if (it != _tree_node_index.end())	// find p0 record
	{
		it->second = pBTreeNode_Disk<_Key, _Val>(new BTreeNode_Disk<_Key, _Val>(p));
		_STD cout << "modified a node" << _STD endl;
	}
	else
	{
		// create new node
		_tree_node_index.insert(_MyPair(p->get_id(), new BTreeNode_Disk<_Key, _Val>(p)));
		_STD cout << "created a node" << _STD endl;
	}
	// remove p0 data
	p->_valid = false;
	p->_keys.clear();
	p->_c.clear();
	p->_vals.clear();
	p->_leaf = true;
}

template <typename _Key, typename _Val>
void DiskSimulator<_Key, _Val>::disk_read(pBTreeNode<_Key, _Val> &x)
{
	// simulate disk write delay time
	disk_read_delay();
	// search p0->_id
	typename _MyMap::iterator it = _tree_node_index.find(x->get_id());
	if (it != _tree_node_index.end())	// find p0 record
	{
		BTNode_Disk_to_BTNode<_Key, _Val>(it->second, x);
		_STD cout << "read a node" << _STD endl;
	}
	else
	{
		throw Bad_NodeNotFound();
	}
}

template <typename _Key, typename _Val>
inline void DiskSimulator<_Key, _Val>::disk_write_delay()const
{
	sleep(8);
}

template <typename _Key, typename _Val>
inline void DiskSimulator<_Key, _Val>::disk_read_delay()const
{
	sleep(8);
}

template <typename _Key, typename _Val>
void DiskSimulator<_Key, _Val>::sleep(unsigned n_ms)const
{
	_STD chrono::milliseconds delay_time(n_ms);
	_STD this_thread::sleep_for(delay_time);
}

template <typename _Key, typename _Val>
inline void DiskSimulator<_Key, _Val>::check_node(const pBTreeNode<_Key, _Val> &p)const
{
	if (!p->_valid)
	{
		throw(Bad_DataInvalid());
	}
}


_END_ZHF_LIB // end namespace zhf_lib

#endif // !__INC_DISK_HPP

