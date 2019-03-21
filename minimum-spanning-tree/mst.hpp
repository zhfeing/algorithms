#ifndef __INC_MST_HPP
#define __INC_MST_HPP

#include "graph.hpp"
#include "priority_queue.hpp"

#include <limits>
#include <string>

#ifndef _BEGIN_ZHF_LIB
#define _BEGIN_ZHF_LIB namespace zhf_lib{
#endif // !_BEGIN_ZHF_LIB

#ifndef _END_ZHF_LIB
#define _END_ZHF_LIB }
#endif // !_END_ZHF_LIB

_BEGIN_ZHF_LIB

const int IntMax = std::numeric_limits<int>::max();

template <class _Data, 
	class Weight_Type = unsigned>
class MST_GraphNode
	: public _NodeBase<_Data>
{
public:
	explicit inline MST_GraphNode(const unsigned id) :_NodeBase<_Data>(id)
	{
		pi = nullptr;
		weight = IntMax;
	}
	explicit inline MST_GraphNode(const _Data &data, unsigned id) :_NodeBase<_Data>(data, id)
	{
		pi = nullptr;
		weight = IntMax;
	}
	inline explicit MST_GraphNode(const MST_GraphNode &n) 
		:_NodeBase<_Data>(n), pi(n.pi), son(n.son), weight(n.weight){ }
	virtual MST_GraphNode& operator=(const MST_GraphNode& rhs)
	{
		if (&rhs != this)
		{
			delete this->data;
			this->data = new _Data(*rhs.data);
			this->id = rhs.id;
			pi = rhs.pi;
			son = rhs.son;
			weight = rhs.weight;
		}
		return *this;
	}
	MST_GraphNode *pi;
	list<MST_GraphNode*>son;
	WeightedEdge<Weight_Type> weight;
};

template <class _Data>
class Node_CMP
{
public:
	bool operator()(const MST_GraphNode<_Data> *l, const MST_GraphNode<_Data> *r)const
	{
		return l->weight > r->weight;
	}
};

template <class _Data, 
	class Weight_Type = unsigned>
MST_GraphNode<_Data> *MST(WeightedGraphMatrix<_Data, MST_GraphNode<_Data>, WeightedEdge<Weight_Type>> &graph)
{
	typedef MST_GraphNode<_Data> Node;
	Node *root = graph.get_node(0);
	zhf_lib::PriorityQueue<Node*, Node_CMP<_Data>> Q;
	// initial steps
	graph.get_node(0)->weight = 0;
	graph.get_node(0)->pi = nullptr;
	Q.push(graph.get_node(0));
	for (unsigned i = 1; i < graph.size(); i++)
	{
		graph.get_node(i)->weight = IntMax;
		graph.get_node(i)->pi = nullptr;
		Q.push(graph.get_node(i));
	}
	while (!Q.empty())
	{
		MST_GraphNode<_Data> *n = Q.top();	// extract smallest weight vertex
		Q.pop();
		const vector<bool> adj_vertices = graph.get_adj_vertices(n->get_id());
		for (auto iter = adj_vertices.begin(); iter != adj_vertices.end(); iter++)
		{
			if (*iter)	// is a adj vertex
			{
				_Index new_id = iter - adj_vertices.begin();
				if (!Q.has_id(new_id))
				{
					continue;
				}
				Node *adj_node = Q.at(new_id);
				if (Q.at(new_id)->weight < graph.get_edge_weight(n, adj_node))	// can decrease weight
				{
					//Node *new_node = adj_node;
					adj_node->weight = graph.get_edge_weight(n, adj_node);
					Q.change_key(new_id, adj_node);
					graph.get_node(new_id)->pi = graph.get_node(n->get_id());
				}
			}
		}
	}
	for (auto index = 0; index < graph.size(); index++)
	{
		Node *pi;
		if ((pi = graph.get_node(index)->pi) != nullptr)
		{
			pi->son.push_back(graph.get_node(index));
		}
	}
	return root;
}

template <class _Data,
	class Weight_Type = unsigned>
	MST_GraphNode<_Data> *MST(WeightedGraphList<_Data, MST_GraphNode<_Data>, WeightedEdge<Weight_Type>> &graph)
{
	typedef MST_GraphNode<_Data> Node;
	Node *root = graph.get_node(0);
	zhf_lib::PriorityQueue<Node*, Node_CMP<_Data>> Q;
	// initial steps
	graph.get_node(0)->weight = 0;
	graph.get_node(0)->pi = nullptr;
	Q.push(graph.get_node(0));
	for (unsigned i = 1; i < graph.size(); i++)
	{
		graph.get_node(i)->weight = IntMax;
		graph.get_node(i)->pi = nullptr;
		Q.push(graph.get_node(i));
	}
	while (!Q.empty())
	{
		MST_GraphNode<_Data> *n = Q.top();	// extract smallest weight vertex
		Q.pop();
		//for(graph.)
	}

	return root;
}
_END_ZHF_LIB

#endif