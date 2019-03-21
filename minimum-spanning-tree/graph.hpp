#ifndef __INC_GRAPH_HPP
#define __INC_GRAPH_HPP

#pragma once
#include <list>
#include <vector>
#include <stack>
#include <iostream>
#include <utility>
#include <limits>
#include <functional>


#ifndef _BEGIN_ZHF_LIB
#define _BEGIN_ZHF_LIB namespace zhf_lib{
#endif // !_BEGIN_ZHF_LIB

#ifndef _END_ZHF_LIB
#define _END_ZHF_LIB }
#endif // !_END_ZHF_LIB


_BEGIN_ZHF_LIB

using std::list;
using std::vector;
using std::stack;
using std::pair;

/*The basic class for a vertex of a graph*/
template <class _Data>
class _NodeBase
{
public:
	inline explicit _NodeBase(const unsigned id)
		:id(id)
	{
		data = nullptr;
	}
	inline explicit _NodeBase(const _Data &data, unsigned id)
		:id(id)
	{
		this->data = new _Data(data);
	}
	inline explicit _NodeBase(const _NodeBase &n)
	{
		data = new _Data(*n.data);
		id = n.id;
	}
	virtual ~_NodeBase()
	{
		std::cout << "delete node " << id << std::endl;
		delete data;
	}
	virtual _NodeBase& operator=(const _NodeBase& rhs)
	{
		if (&rhs != this)
		{
			delete data;
			data = new _Data(*rhs.data);
			id = rhs.id;
		}
		return *this;
	}
	_Data *data;
	inline unsigned get_id()
	{
		return id;
	}
protected:
	unsigned id;
};

/*The basic class for represent a graph
*type name 'Data' and 'Node' can be set by given that 'Node' is 
*inherited from class '_NodeBase'
*/
template <class _Data,
	class _Node = _NodeBase<_Data>>
class _Graph_Base
{
public:
	inline _Graph_Base(const size_t size, const vector<_Data> &nodes_data) :s(size)
	{
		nodes.resize(size);
		initial_nodes(nodes_data);
	}
	~_Graph_Base()
	{
		for (unsigned i = 0; i < nodes.size(); i++)
		{
			delete nodes[i];
		}
	}
	inline virtual _Node *get_node(unsigned index)
	{
		return nodes.at(index);
	}
	inline virtual size_t size()
	{
		return s;
	}
private:
	void initial_nodes(const vector<_Data> &nodes_data)
	{
		for (unsigned i = 0; i < nodes.size(); i++)
		{
			nodes[i] = new _Node(_Data(nodes_data[i]), i);
		}
	}
protected:
	vector<_Node*> nodes;
	size_t s;
};

/*Weight can only be C++ numeric data like int, unsigned, ...*/
template <class _Weight>
class WeightedEdge
{
public:
	WeightedEdge()
	{
		weight = _Weight(0);
	}
	WeightedEdge(const _Weight &w)
	{
		weight = w;
	}
	_Weight weight;
	const static WeightedEdge MaxWeight;
};

template <class _Weight>
bool operator<(const _Weight &lhs, const _Weight &rhs)
{
	return lhs.weight > rhs.weight;
}

template <class _Weight>
bool operator>(const _Weight &lhs, const _Weight &rhs)
{
	return lhs.weight > rhs.weight;
}


template <class _Weight>
const WeightedEdge<_Weight> WeightedEdge<_Weight>::MaxWeight(std::numeric_limits<_Weight>::max());


/*class 'GraphMatrix' represent a graph in a matrix*/
template <class _Data, 
	class _Node = _NodeBase<_Data>>
class GraphMatrix
	: public _Graph_Base<_Data, _Node>
{
public:
	GraphMatrix(const size_t size, const vector<_Data> &nodes_data, const vector<vector<bool>> &adjMatrix)
		: _Graph_Base<_Data, _Node>(size, nodes_data)
	{
		adj_matrix.resize(size);
		for (auto iter = adj_matrix.begin(); iter != adj_matrix.end(); iter++)
		{
			iter->resize(size, false);
		}
		initial_adj_matrix(adjMatrix);
	}
private:
	void initial_adj_matrix(const vector<vector<bool>> &adjMatrix)
	{
		for (unsigned i = 0; i < adj_matrix.size(); i++)
		{
			for (unsigned j = 0; j < adj_matrix[i].size(); j++)
			{
				adj_matrix[i][j] = adjMatrix[i][j];
			}
		}
	}
	vector<vector<bool>> adj_matrix;
};

/*class 'GraphList' represent a graph in the form of adj-list*/
template <class _Data, 
	class _Node = _NodeBase<_Data>>
class GraphList
	:public _Graph_Base<_Data, _Node>
{
public:
	GraphList(const size_t size, const vector<_Data> &nodes_data)
		:_Graph_Base<_Data, _Node>(size, nodes_data)
	{
		for (auto iter = this->nodes.begin(); iter != this->nodes.end(); iter++)
		{
			adj_list[*iter] = list<_NodeBase<_Data>*>();
		}
	}
	GraphList(const size_t size, const vector<_Data> &nodes_data, const vector<vector<bool>> &adj_matrix)
		:_Graph_Base<_Data, _Node>(size, nodes_data)
	{
		for (unsigned i = 0; i < this->nodes.size(); i++)
		{
			adj_list[nodes[i].id] = list<_Node*>();
			for (unsigned j = 0; j < nodes.size(); j++)
			{
				if (adj_matrix[i][j])	// connected
				{
					adj_list[nodes[i].id].push_back(nodes[j]);
				}
			}
		}
	}
private:
	vector<list<_Node*>> adj_list;
};


/*interface of weighted graph*/
template <class _Data,
	class _Node = _NodeBase<_Data>, 
	class _Weight = WeightedEdge<unsigned>>
class _WeightedGraph_Base
	: public _Graph_Base<_Data, _Node>
{
public:
	inline _WeightedGraph_Base(const size_t size, const vector<_Data> &nodes_data) 
		:_Graph_Base<_Data, _Node>(size, nodes_data) { }
	inline virtual _Weight get_edge_weight(_Node *, _Node *) = 0;
};


/*class 'WeightedGraphMatrix' add weighted edges of a graph, Weight can only inherited from 'WeightedEdge'*/
template <class _Data, 
	class _Node = _NodeBase<_Data>, 
	class _Weight = WeightedEdge<unsigned>>
class WeightedGraphMatrix
	: public _WeightedGraph_Base<_Data, _Node, _Weight>
{
public:
	WeightedGraphMatrix(const size_t size, const vector<_Data> &nodes_data, 
		const vector<vector<bool>> &adjMatrix, const vector<vector<_Weight>> &edgeWeight)
		: _WeightedGraph_Base<_Data, _Node, _Weight>(size, nodes_data)
	{
		edge_weight.resize(size);
		for (auto iter = edge_weight.begin(); iter != edge_weight.end(); iter++)
		{
			iter->resize(size, _Weight());
		}
		initial_edge_weight(edgeWeight);

		adj_matrix.resize(size);
		for (auto iter = adj_matrix.begin(); iter != adj_matrix.end(); iter++)
		{
			iter->resize(size, false);
		}
		initial_adj_matrix(adjMatrix);
	}
	inline virtual _Weight get_edge_weight(_Node *u, _Node *v)
	{
		return edge_weight[u->get_id()][v->get_id()];
	}
	const vector<bool> &get_adj_vertices(unsigned id)
	{
		return adj_matrix.at(id);
	}
private:
	void initial_edge_weight(const vector<vector<_Weight>> &edgeWeight)
	{
		for (unsigned i = 0; i < edge_weight.size(); i++)
		{
			for (unsigned j = 0; j < edge_weight[i].size(); j++)
			{
				edge_weight[i][j] = edgeWeight[i][j];
			}
		}
	}
	void initial_adj_matrix(const vector<vector<bool>> &adjMatrix)
	{
		for (unsigned i = 0; i < adj_matrix.size(); i++)
		{
			for (unsigned j = 0; j < adj_matrix[i].size(); j++)
			{
				adj_matrix[i][j] = adjMatrix[i][j];
			}
		}
	}
	vector<vector<_Weight>> edge_weight;
	vector<vector<bool>> adj_matrix;
};

template <class _Data,
	class _Node = _NodeBase<_Data>,
	class _Weight = WeightedEdge<unsigned>>
	class WeightedGraphList
	:public _WeightedGraph_Base<_Data, _Node, _Weight>
{
public:
	using _WeightedEdge = pair<_Node*, _Weight>;
	WeightedGraphList(const size_t size, const vector<_Data> &nodes_data, 
		const vector<vector<bool>> &adj_matrix, const vector<vector<_Weight>> &edgeWeight)
		:_WeightedGraph_Base<_Data, _Node, _Weight>(size, nodes_data)
	{
		adj_list.resize(size);
		for (unsigned i = 0; i < this->nodes.size(); i++)
		{
			adj_list[this->nodes[i]->get_id()] = list<_WeightedEdge>();
			for (unsigned j = 0; j < this->nodes.size(); j++)
			{
				if (adj_matrix[i][j])	// connected
				{
					adj_list[this->nodes[i]->get_id()].push_back(_WeightedEdge(this->nodes[j], edgeWeight[i][j]));
				}
			}
		}
	}
	inline virtual _Weight get_edge_weight(_Node *u, _Node *v)
	{
		for (auto iter = adj_list[u->get_id()].begin(); iter != adj_list[u->get_id()].end(); iter++)
		{
			if (iter->first == v)	// find edge (u, v)
			{
				return iter->second;
			}
		}
		return _Weight::MaxWeight;
	}
	const list<_WeightedEdge> &get_adj_get_adj_vertices(unsigned id)
	{
		return adj_list.at(id);
	}
private:
	vector<list<_WeightedEdge>> adj_list;
};

_END_ZHF_LIB

#endif // !__INC_GRAPH_HPP
