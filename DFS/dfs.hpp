#pragma once
#ifndef __INC_DFS_HPP
#define __INC_DFS_HPP

#include <list>
#include <vector>
#include <stack>
#include <utility>

using std::list;
using std::vector;
using std::pair;
using std::stack;

typedef unsigned Time;

template <class _Data>
class Node
{
public:
	Node()
	{
		data = nullptr;
		visited = false;
		d = 0;
		f = 0;
		id = 0;
		pi = nullptr;
	}
	~Node()
	{
		delete data;
	}
	
	Time d, f;	// d is node discovered time, f is finish visit this node time
	_Data *data;
	unsigned id;
	bool visited;
	Node *pi;
};


template<typename _Data>
vector<pair<Node<_Data>*, list<Node<_Data>*>>> 
adj_matrix2list(vector<Node<_Data>*> nodes, vector<vector<bool>> &adj_matrix)
{
	vector<pair<Node<_Data>*, list<Node<_Data>*>>>adj_list;
	adj_list.clear();
	adj_list.resize(nodes.size());
	for (unsigned i = 0; i < nodes.size(); i++)
	{
		adj_list[i].first = nodes[i];
		adj_list[i].second.clear();
		for (unsigned j = 0; j < nodes.size(); j++)
		{
			if (adj_matrix[i][j])	// connected
			{
				adj_list[i].second.push_back(nodes[j]);
			}
		}
	}
	return adj_list;
}

template<typename _Data>
list<Node<_Data>*> dfs_search(vector<Node<_Data>*> &nodes, const vector<vector<bool>> &adj_matrix, int key)
{
	Time time = 1;
	list<Node<_Data>*> find_result;

	// clear previous marks
	for (auto iter = nodes.begin(); iter != nodes.end(); iter++)
	{
		(*iter)->visited = false;
		(*iter)->id = iter - nodes.begin();
	}

	for (auto iter = nodes.begin(); iter != nodes.end(); iter++)
	{
		if (!(*iter)->visited)
		{
			// visit this node
			stack<Node<_Data>*> visit_stack;
			(*iter)->visited = true;
			(*iter)->d = time++;
			(*iter)->pi = nullptr;
			visit_stack.push(*iter);
			Node<_Data>* top;
			while (!visit_stack.empty())
			{
				// check adj_matrix to find a point not visited
				bool has_adj_vetex = false;
				top = visit_stack.top();
				for (unsigned i = 0; i < nodes.size(); i++)
				{
					if (adj_matrix[top->id][i] && !nodes[i]->visited)
					{
						nodes[i]->d = time++;
						nodes[i]->visited = true;
						nodes[i]->pi = top;
						visit_stack.push(nodes[i]);
						top = visit_stack.top();
						has_adj_vetex = true;
						break;
					}
				}
				if (!has_adj_vetex)
				{
					// no adj vetices
					top->f = time++;
					if (*(top->data) == key)
					{
						find_result.push_back(top);
					}
					visit_stack.pop();
				}
			}
		}
	}
	return find_result;
}

template<typename _Data>
list<Node<_Data>*> dfs_search(vector<pair<Node<_Data>*, list<Node<_Data>*>>> &adj_list, int key)
{
	list<Node<_Data>*> res;
	Time time = 1;
	// clear visit trace
	for (auto iter = adj_list.begin(); iter != adj_list.end(); iter++)
	{
		iter->first->visited = false;
		iter->first->id = iter - adj_list.begin();
	}
	// dfs
	for (auto iter = adj_list.begin(); iter != adj_list.end(); iter++)
	{
		if (!iter->first->visited)
		{
			stack<Node<_Data>*> visit_stack;
			iter->first->visited = true;
			iter->first->d = time++;
			iter->first->pi = nullptr;
			visit_stack.push(iter->first);
			Node<_Data>* top;
			while (!visit_stack.empty())
			{
				// check adj_matrix to find a point not visited
				bool has_adj_vetex = false;
				top = visit_stack.top();
				// check the adj table
				// notice the grammer here that typename is used when templates are nesting
				for (typename list<Node<_Data>*>::iterator adj_vertex = adj_list[top->id].second.begin();
					adj_vertex != adj_list[top->id].second.end(); adj_vertex++)
				{
					if (!(*adj_vertex)->visited)
					{
						(*adj_vertex)->d = time++;
						(*adj_vertex)->visited = true;
						(*adj_vertex)->pi = top;
						visit_stack.push(*adj_vertex);
						top = visit_stack.top();
						has_adj_vetex = true;
						break;
					}
				}
				if (!has_adj_vetex)
				{
					// no adj vetices
					top->f = time++;
					if (*(top->data) == key)
					{
						res.push_back(top);
					}
					visit_stack.pop();
				}
			}
		}
	}
	return res;
}

#endif // !__INC_DFS_HPP

