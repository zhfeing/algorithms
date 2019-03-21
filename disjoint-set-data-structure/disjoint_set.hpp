#ifndef __INC_DDS_HPP
#define __INC_DDS_HPP

#include <algorithm>
#include <utility>
#include <iostream>
#include <vector>
#include <unordered_set>

/* just for convenient */
#define _ZHF_LIB namespace zhf_lib {
#define _END_ZHF_LIB }

/* begin dds.hpp */
_ZHF_LIB

#ifndef _STD
#define _STD ::std::
#endif // !_STD

// pre-declaration
template<class _Val>
class DisjointSet_List;

template<class _Val>
class DisjointSet_Tree;

template<typename _Val>
_STD ostream &operator<<(_STD ostream &out, DisjointSet_List<_Val>&d);

template<typename _Val>
_STD ostream &operator<<(_STD ostream &out, DisjointSet_Tree<_Val>&d);

// exceptions
template<class _Val>
class Bad_ValueInvalid
{
};

class Bad_Node
{
};

template<class _Node>
class DisjointSet_Head
{
public:
	size_t rank;
	_Node *first_item, *last_item;
};

template<class _Val>
class DisjointSet_ListNode
{
public:
	using _Node = DisjointSet_ListNode;
	using _Head = DisjointSet_Head<_Node>;
	friend class DisjointSet_List<_Val>;
	template<typename _T>
	friend _STD ostream &operator<<(_STD ostream &out, DisjointSet_List<_T>&d);
public:
	explicit DisjointSet_ListNode(const DisjointSet_List<_Val>&);
	explicit DisjointSet_ListNode(const _Val &, const DisjointSet_List<_Val>&);
	void set_val(const _Val &);
	~DisjointSet_ListNode();
private:
	DisjointSet_ListNode(const _Node &);
	_Node & operator=(const _Val &);
private:
	_Val * _val;
	_Head *_head;
	_Node *_next;
	const DisjointSet_List<_Val> *_owner;
	bool _valid;
};

template<class _Val>
class DisjointSet_TreeNode
{
public:
	using _Node = DisjointSet_TreeNode;
	using _Head = DisjointSet_Head<_Node>;
	friend class DisjointSet_Tree<_Val>;
	template<typename _T>
	friend _STD ostream &operator<<(_STD ostream &out, DisjointSet_Tree<_T>&d);
public:
	explicit DisjointSet_TreeNode(const DisjointSet_Tree<_Val>&);
	explicit DisjointSet_TreeNode(const _Val &, const DisjointSet_Tree<_Val>&);
	void set_val(const _Val &);
	~DisjointSet_TreeNode();
private:
	DisjointSet_TreeNode(const _Node &);
	_Node & operator=(const _Val &);
private:
	_Val * _val;
	_Head *_head;
	_STD list<_Node*> _sub_trees;
	const DisjointSet_Tree<_Val> *_owner;
	bool _valid;
};


// class just manage properities of its nodes, but does not save its nodes
template<class _Val>
class DisjointSet_List
{
public:
	using _Node = DisjointSet_ListNode<_Val>;
	using _Head = DisjointSet_Head<_Node>;
public:
	DisjointSet_List();
	~DisjointSet_List();
	void make_set(_Node &);
	const _Head &find_set(const _Node &);
	void union_set(_Node &, _Node &);
	size_t size();
	const _STD unordered_set<_Head*> &get_heads();

private:
	// functions that is invalid
	DisjointSet_List(const DisjointSet_List&);
	DisjointSet_List &operator=(const DisjointSet_List&);
private:
	bool check_node(const _Node &);
	void merge(_Node & dst, _Node &src);
private:
	_STD unordered_set<_Head*>_heads;
};


// class just manage properities of its nodes, but does not save its nodes
template<class _Val>
class DisjointSet_Tree
{
public:
	using _Node = DisjointSet_TreeNode<_Val>;
	using _Head = DisjointSet_Head<_Node>;
public:
	DisjointSet_Tree();
	~DisjointSet_Tree();
	void make_set(_Node &);
	const _Head &find_set(const _Node &);
	void union_set(_Node &, _Node &);
	size_t size();
	const _STD unordered_set<_Head*> &get_heads();

private:
	// functions that is invalid
	DisjointSet_Tree(const DisjointSet_Tree&);
	DisjointSet_Tree &operator=(const DisjointSet_Tree&);
private:
	bool check_node(const _Node &);
	void merge(_Node & dst, _Node &src);
private:
	_STD unordered_set<_Head*>_heads;

};

// relaization

/*class DisjointSet_ListNode*/
template<class _Val>
DisjointSet_ListNode<_Val>::DisjointSet_ListNode(const DisjointSet_List<_Val> &owner)
	:_val(nullptr), _next(nullptr), _head(nullptr), _owner(&owner), _valid(false)
{
}

template<class _Val>
DisjointSet_ListNode<_Val>::DisjointSet_ListNode(const _Val &val, const DisjointSet_List<_Val> &owner)
	: _next(nullptr), _head(nullptr), _owner(&owner), _valid(false)
{
	_val = new _Val(val);
}

template<class _Val>
void DisjointSet_ListNode<_Val>::set_val(const _Val &val)
{
	_val = new _Val(val);
}

template<class _Val>
DisjointSet_ListNode<_Val>::~DisjointSet_ListNode()
{
	cout << "delete a node: " << *_val << endl;
	delete _val;
}



/*class DisjointSet_TreeNode*/
template<class _Val>
DisjointSet_TreeNode<_Val>::DisjointSet_TreeNode(const DisjointSet_Tree<_Val> &owner)
	:_val(nullptr), _head(nullptr), _owner(&owner), _valid(false)
{
}

template<class _Val>
DisjointSet_TreeNode<_Val>::DisjointSet_TreeNode(const _Val &val, const DisjointSet_Tree<_Val> &owner)
	:_head(nullptr), _owner(&owner), _valid(false)
{
	_val = new _Val(val);
}

template<class _Val>
void DisjointSet_TreeNode<_Val>::set_val(const _Val &val)
{
	_val = new _Val(val);
}

template<class _Val>
DisjointSet_TreeNode<_Val>::~DisjointSet_TreeNode()
{
	cout << "delete a node: " << *_val << endl;
	delete _val;
}



/*class DisjointSet_List*/
template<class _Val>
DisjointSet_List<_Val>::DisjointSet_List()
{
}

template<class _Val>
DisjointSet_List<_Val>::~DisjointSet_List()
{
	for (auto iter = _heads.begin(); iter != _heads.end(); iter++)
	{
		delete *iter;
	}
	cout << "delete a DisjointSet_List with size: " << _heads.size() << endl;
}

template<class _Val>
void DisjointSet_List<_Val>::make_set(_Node &_n)
{
	_n._valid = true;
	if (!check_node(_n))
	{
		throw Bad_Node();
	}
	// create a new head
	_Head *new_head = new _Head();
	new_head->first_item = &_n;
	new_head->last_item = &_n;
	new_head->rank = 1;
	_heads.insert(new_head);

	// change node n properity
	_n._head = new_head;
	_n._next = nullptr;
	_n._valid = true;
}

template<class _Val>
const DisjointSet_Head<DisjointSet_ListNode<_Val>> &
DisjointSet_List<_Val>::find_set(const _Node &_n)
{
	if (!check_node(_n))
	{
		throw Bad_Node();
	}
	return *(_n._head);
}

template<class _Val>
void DisjointSet_List<_Val>::union_set(_Node &_n1, _Node &_n2)
{
	if (!check_node(_n1) || !check_node(_n2))
	{
		throw Bad_Node();
	}
	if (&find_set(_n1) != &find_set(_n2))		// do not need to union if _n1 and _n2 are in the same set
	{
		if (_n1._head->rank > _n2._head->rank)
		{
			merge(_n1, _n2);
		}
		else
		{
			merge(_n2, _n1);
		}
	}
}

template<class _Val>
size_t DisjointSet_List<_Val>::size()
{
	return _heads.size();
}

template<class _Val>
const _STD unordered_set<DisjointSet_Head<DisjointSet_ListNode<_Val>>*> &
DisjointSet_List<_Val>::get_heads()
{
	return _heads;
}

template<class _Val>
bool DisjointSet_List<_Val>::check_node(const _Node &_n)
{
	return _n._owner == this && _n._valid;
}

template<class _Val>
void DisjointSet_List<_Val>::merge(_Node & dst, _Node &src)
{
	_Head *tmp_head = src._head;
	_Node *n = &src;
	while (n != nullptr)
	{
		n->_head = dst._head;
		n = n->_next;
	}
	dst._head->last_item->_next = tmp_head->first_item;
	dst._head->last_item = tmp_head->last_item;

	_heads.erase(tmp_head);
	delete tmp_head;

	dst._head->rank++;
}	



/*class DisjointSet_Tree*/
template<class _Val>
DisjointSet_Tree<_Val>::DisjointSet_Tree()
{
}

template<class _Val>
DisjointSet_Tree<_Val>::~DisjointSet_Tree()
{
	for (auto iter = _heads.begin(); iter != _heads.end(); iter++)
	{
		delete *iter;
	}
	cout << "delete a DisjointSet_List with size: " << _heads.size() << endl;
}

template<class _Val>
void DisjointSet_Tree<_Val>::make_set(_Node &_n)
{
	_n._valid = true;
	if (!check_node(_n))
	{
		throw Bad_Node();
	}
	// create a new head
	_Head *new_head = new _Head();
	new_head->first_item = &_n;
	new_head->last_item = &_n;
	new_head->rank = 1;
	_heads.insert(new_head);

	// change node n properity
	_n._head = new_head;
	_n._next = nullptr;
	_n._valid = true;
}

template<class _Val>
const DisjointSet_Head<DisjointSet_TreeNode<_Val>> &
DisjointSet_Tree<_Val>::find_set(const _Node &_n)
{
	if (!check_node(_n))
	{
		throw Bad_Node();
	}
	return *(_n._head);
}

template<class _Val>
void DisjointSet_Tree<_Val>::union_set(_Node &_n1, _Node &_n2)
{
	if (!check_node(_n1) || !check_node(_n2))
	{
		throw Bad_Node();
	}
	if (&find_set(_n1) != &find_set(_n2))		// do not need to union if _n1 and _n2 are in the same set
	{
		if (_n1._head->rank > _n2._head->rank)
		{
			merge(_n1, _n2);
		}
		else
		{
			merge(_n2, _n1);
		}
	}
}

template<class _Val>
size_t DisjointSet_Tree<_Val>::size()
{
	return _heads.size();
}

template<class _Val>
const _STD unordered_set<DisjointSet_Head<DisjointSet_TreeNode<_Val>>*> &
DisjointSet_List<_Val>::get_heads()
{
	return _heads;
}

template<class _Val>
bool DisjointSet_Tree<_Val>::check_node(const _Node &_n)
{
	return _n._owner == this && _n._valid;
}

template<class _Val>
void DisjointSet_Tree<_Val>::merge(_Node & dst, _Node &src)
{
	_Head *tmp_head = src._head;
	_Node *n = &src;
	while (n != nullptr)
	{
		n->_head = dst._head;
		n = n->_next;
	}
	dst._head->last_item->_next = tmp_head->first_item;
	dst._head->last_item = tmp_head->last_item;

	_heads.erase(tmp_head);
	delete tmp_head;

	dst._head->rank++;
}




template<typename _Val>
_STD ostream &operator<<(_STD ostream &out, DisjointSet_List<_Val>&d)
{
	out << "-----------------------------------------------" << _STD endl;
	if (d.size() == 0)
	{
		out << "empty set" << _STD endl;
	}
	const _STD unordered_set<DisjointSet_Head<DisjointSet_ListNode<_Val>>*> heads = d.get_heads();
	int i = 0;
	for (auto iter = heads.begin(); iter != heads.end(); iter++, ++i)
	{
		out << "set " << i << ": \t{";
		for (DisjointSet_ListNode<_Val>* node = (*iter)->first_item; node != nullptr; node = node->_next)
		{
			out << *(node->_val) << ", ";
		}
		out << "}" << _STD endl;
	}
	out << "-----------------------------------------------" << _STD endl;
	return out;
}

template<typename _Val>
_STD ostream &operator<<(_STD ostream &out, DisjointSet_Tree<_Val>&d)
{
	out << "-----------------------------------------------" << _STD endl;
	if (d.size() == 0)
	{
		out << "empty set" << _STD endl;
	}
	const _STD unordered_set<DisjointSet_Head<DisjointSet_TreeNode<_Val>>*> heads = d.get_heads();
	int i = 0;
	for (auto iter = heads.begin(); iter != heads.end(); iter++, ++i)
	{
		out << "set " << i << ": \t{";
		for (DisjointSet_TreeNode<_Val>* node = (*iter)->first_item; node != nullptr; node = node->_next)
		{
			out << *(node->_val) << ", ";
		}
		out << "}" << _STD endl;
	}
	out << "-----------------------------------------------" << _STD endl;
	return out;
}



_END_ZHF_LIB

#endif // !__INC_DDS_HPP
