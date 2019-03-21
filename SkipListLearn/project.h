#pragma once
#ifndef __INC_PROJECT
#define __INC_PROJECT
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <iostream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

//Key(-1) is the min key
template<class Key>
class LinkedList;
template<class Key>
class SkipList;


template<class Key>
class Node
{	
protected:
	Node *n, *p;
	Key k;
	Node *u, *d;
private:
	static Node *const NIL;

	friend LinkedList<Key>;
	friend SkipList<Key>;
public:
	Node();
	Node(Key);
	Node(Key key, Node *next, Node *previous, Node *up, Node *down)
		:k(key), n(next), p(previous), u(up), d(down)
	{
	}
	virtual Node<Key> *next()
	{
		return n;
	}
	virtual Node<Key> *previous()
	{
		return p;
	}
	virtual Node<Key> *up()
	{ 
		return u;
	}
	virtual Node<Key> *down()
	{
		return d;
	}
	Key key()
	{
		return k;
	}
};

template<class Key>
Node<Key> *const Node<Key>::NIL = new Node;
template<class Key>
Node<Key>::Node()
	:n(nullptr), p(nullptr), k(), u(nullptr), d(nullptr)
{
}
template<class Key>
Node<Key>::Node(Key key)
	:n(nullptr), p(nullptr), k(key), u(nullptr), d(nullptr)
{
}

template<class Key>
class LinkedList
{
public:
	LinkedList();
	virtual ~LinkedList();
	Node<Key> *root()
	{
		return r;
	}
	virtual void insert(Key);
	virtual void print(Node<Key> *);
	virtual void delete_node(Node<Key> *);
	virtual Node<Key> *search(Key);

	class Bad_Node{ };
	class Bad_operator{ };
protected:
	/* r->n is thr first element, r->p is the last element */
	Node<Key> *r;
private:
	LinkedList operator=(LinkedList)
	{
		throw(Bad_operator());
	}
	LinkedList(LinkedList &)
	{
		throw(Bad_operator());
	}
};

template<class Key>
LinkedList<Key>::LinkedList()
{
	r = new Node<Key>;
	r->n = Node<Key>::NIL;
	r->p = Node<Key>::NIL;
	r->k = Key();
}
template<class Key>
LinkedList<Key>::~LinkedList()
{
	auto x = r->n;
	while (x != Node<Key>::NIL)
	{
		x = x->n;
		delete x->p;
	}
	delete r;
}
template<class Key>
void LinkedList<Key>::insert(Key key)
{
	Node<Key> *z = new Node<Key>(key);
	z->u = Node<Key>::NIL;
	z->d = Node<Key>::NIL;
	Node<Key> *x = r->n;	//x points to the first one
	Node<Key> *y = Node<Key>::NIL;
	while (x != Node<Key>::NIL && x->k < key)
	{
		y = x;
		x = x->n;
	}
	if (y == Node<Key>::NIL)			//insert to the head of list
	{
		z->n = r->n;
		z->p = Node<Key>::NIL;
		if (r->n != Node<Key>::NIL)		//not a empty list
		{
			r->n->p = z;
		}
		r->n = z;
	}
	else
	{
		y->n = z;
		z->p = y;
		z->n = x;
		if (x != Node<Key>::NIL)					//not insert to the end
		{
			x->p = z;
		}
		else
		{
			r->p = z;
		}
	}
}
template<class Key>
void LinkedList<Key>::print(Node<Key> *start)
{
	if (start == r)
		start = start->n;
	for (Node<Key> *y = start; y != Node<Key>::NIL; y = y->n)
	{
		cout << y->k << endl;
	}
}
template<class Key>
void LinkedList<Key>::delete_node(Node<Key> *x)
{
	if (x == r || x == Node<Key>::NIL)
	{
		throw(Bad_Node());
	}
	if (x->p != Node<Key>::NIL)		//x is not head
	{
		x->p->n = x->n;
	}
	else
	{
		r->n = x->n;
	}
	if (x->n != Node<Key>::NIL)		//x is not end
	{
		x->n->p = x->p;
	}
	else
	{
		r->p = x->p;
	}
	delete x;
}
template<class Key>
Node<Key> *LinkedList<Key>::search(Key key)
{
	auto x = r;
	while(x != Node<Key>::NIL && x->k != key)
	{
		x = x->n;
	}
	return x;
}


///skip list
//! no mulity-key
template<class Key>
class SkipList
{
private:
	Node<Key> *r;		//r->d = r_top, r->u = r_bottom
	unsigned levelNum;
	static Node<Key> *newLevel();
	/*in one level, if find key return key pointer, 
	else return pointer to the biggest element smaller than key*/
	static Node<Key> *findPosition(Node<Key> *, Key);
	void deleteNodeInLevel(Node<Key> *);
public:
	SkipList();
	~SkipList();
	void insert(Key);
	void deleteNode(Node<Key> *);
	void print();
	bool empty();
	Node<Key> *search(Key);
	class Bad_Node
	{
	};
	class Bad_Operator
	{
	};
	class Bad_Key
	{
	};
};

template<class Key>
SkipList<Key>::SkipList()
{
	r = new Node<Key>;
	r->n = Node<Key>::NIL;
	r->p = Node<Key>::NIL;
	r->k = Key();
	levelNum = 1;
	
	Node<Key> *z = newLevel();
	r->d = z;
	r->u = z;
}

template<class Key>
SkipList<Key>::~SkipList()
{
	//delete headers
	auto x = r->d;
	while (x != Node<Key>::NIL)
	{
		//delete elements
		auto y = x->n;
		while (y != Node<Key>::NIL)
		{
			y = y->n;
			delete y->p;
		}
		x = x->d;
		delete x->u;
	}
	delete r;
}

template<class Key>
void SkipList<Key>::insert(Key key)
{
	if (key <= Key(-1))
		throw Bad_Key();
	Node<Key> *z = new Node<Key>(key);
	Node<Key> *y;
	Node<Key> *place = Node<Key>::NIL;		//record x last place
	//find place to insert and record go down place
	stack<Node<Key>*> record;
	for (Node<Key> *x = r->d; x != Node<Key>::NIL; x = x->d)
	{
		y = findPosition(x, key);
		x = y;
		place = x;
		record.push(place);
	}
	z->u = Node<Key>::NIL;
	z->d = Node<Key>::NIL;
	z->p = place;
	z->n = place->n;
	if (place->n != Node<Key>::NIL)
	{
		place->n->p = z;
	}
	place->n = z;
	
	if (record.empty() == false)
		record.pop();				//do not need the last element
	//randomly raise z up
	while (rand() %2 == 1)
	{
		if (record.empty() == false)	//under max hight
		{
			y = record.top();
			Node<Key> *newNode = new Node<Key>(key, y->n, y, Node<Key>::NIL, z);
			z->u = newNode;
			if (y->n != Node<Key>::NIL)
			{
				y->n->p = newNode;
			}
			y->n = newNode;
			z = newNode;

			record.pop();
		}
		else							//need to create a new level
		{
			Node<Key> *newl = newLevel();
			Node<Key> *newNode = new Node<Key>(key);
			newl->u = Node<Key>::NIL;
			newl->d = r->d;
			newl->n = newNode;

			r->d->u = newl;
			r->d = newl;

			newNode->n = Node<Key>::NIL;
			newNode->p = newl;
			newNode->u = Node<Key>::NIL;
			newNode->d = z;

			z->u = newNode;
			z = newNode;
		}
	}
}

template<class Key>
void SkipList<Key>::deleteNodeInLevel(Node<Key> *x)
{
	if (x == nullptr)
		throw Bad_Node();
	else if (x->k == Key(-1))		//not an empty node
	{
		if (x->n != Node<Key>::NIL)
		{
			cerr << "this level have other element and not allow to delete the header" << endl;
			throw Bad_Node();
		}
		if (x->u != Node<Key>::NIL)			//x is not in the top level
		{
			x->u->d = x->d;
			if (x->d == Node<Key>::NIL)		//x is in the bottom level
			{
				r->p = x->u;				//set root bottom pointer
			}
			else
			{
				x->d->u = x->u;
			}
		}
		else
		{
			r->d = x->d;
			if (x->d == Node<Key>::NIL)		//only have one level, not allow to delete
			{
				cerr << "only have one level and not allow to delete" << endl;
				throw Bad_Node();
			}
			else
			{
				x->d->u = Node<Key>::NIL;
			}
		}
	}
	else if (x != Node<Key>::NIL)
	{
		x->p->n = x->n;
		if (x->n != Node<Key>::NIL)
			x->n->p = x->p;
		if (x->u != Node<Key>::NIL)
			x->u->d = x->d;
		if (x->d != Node<Key>::NIL)
			x->d->u = Node<Key>::NIL;
	}
	else
	{
		cerr << "delete a NIL node not allowed" << endl;
		throw Bad_Node();
	}
	delete x;
}

template<class Key>
void SkipList<Key>::deleteNode(Node<Key> *x)
{
	if (x->d != Node<Key>::NIL)	//not bottom level element
	{
		throw Bad_Node();
	}
	if (x == Node<Key>::NIL || x == nullptr)
		throw Bad_Node();
	for (Node<Key> *y; x != Node<Key>::NIL; x = y)
	{
		y = x->u;
		if (x->p->k == Key(-1) && x->n == Node<Key>::NIL)	//this level only have one element
		{
			Node<Key> *header = x->p;
			deleteNodeInLevel(x);
			if (header->d != Node<Key>::NIL || header->u != Node<Key>::NIL)	//have another level
				deleteNodeInLevel(header);
		}
		else
		{
			deleteNodeInLevel(x);
		}
	}
}

template<class Key>
void SkipList<Key>::print()
{
	int i = 0;
	for (auto x = r->d; x != Node<Key>::NIL; x = x->d, i++)
	{
		cout << "level " << i << endl;
		for (auto y = x->n; y != Node<Key>::NIL; y = y->n)
		{
			cout << "key is: " << y->k << "; ";
		}
		cout << endl;
	}
	cout << endl;
}

template<class Key>
Node<Key>* SkipList<Key>::search(Key key)
{
	if (key <= Key(-1))
		throw Bad_Key();
	Node<Key> *x = r->d;
	Node<Key> *y = Node<Key>::NIL;
	while (x != Node<Key>::NIL)
	{
		y = x;
		x = findPosition(x, key)->n;
		if (x == Node<Key>::NIL || x->k > key)	//look up x in the next level
		{
			x = y->d;
		}
		else if(x->k == key)
		{
			y = x;
			break;
		}
		else
		{
			throw Bad_Key();
		}
	}
	if (y->k != key)
	{
		y = Node<Key>::NIL;
		return y;
	}
	else	//go to the bottom of skip list
	{
		while (y != Node<Key>::NIL)
		{
			x = y;
			y = y->d;
		}
		return x;
	}
}

template<class Key>
Node<Key> *SkipList<Key>::newLevel()
{
	Node<Key> *z = new Node<Key>(Key(-1));
	z->u = Node<Key>::NIL;
	z->d = Node<Key>::NIL;
	z->n = Node<Key>::NIL;
	z->p = Node<Key>::NIL;
	return z;
}

template<class Key>
Node<Key> *SkipList<Key>::findPosition(Node<Key> *header, Key key)
{
	Node<Key> *x = header;
	Node<Key> *y = Node<Key>::NIL;
	while (x != Node<Key>::NIL && key > x->k)
	{
		y = x;
		x = x->n;
	}
	return y;
}

template<class Key>
bool SkipList<Key>::empty()
{
	if (r->d->n->->n != Node<Key>::NIL)
		return false;
	else
		return true;
}

#endif // !__INC_PROJECT
