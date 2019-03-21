#include "dfs.hpp"
#include <list>
#include <algorithm>

using std::list;

template <class _Data> 
class DFS_Tree
{
public:
	DFS_Tree *pi;
	list<DFS_Tree*> son;
	Node<_Data> *key;
	DFS_Tree()
	{
		pi = nullptr;
		key = nullptr;
	}	
};

template<class _Data>
class _Compare_F
{
public:
	bool operator()(const pair<Node<_Data>*, list<Node<_Data>*>> &l, 
		const pair<Node<_Data>*, list<Node<_Data>*>> &r)
	{
		return l.first->f > r.first->f;
	}
};
template<class _Data>
class _Compare_D
{
public:
	bool operator()(const pair<Node<_Data>*, list<Node<_Data>*>> &l,
		const pair<Node<_Data>*, list<Node<_Data>*>> &r)
	{
		return l.first->d < r.first->d;
	}
};

template<typename _Data>
list<DFS_Tree<_Data>*> dfs_forest(vector<pair<Node<_Data>*, list<Node<_Data>*>>> &adj_list)
{
	Time time = 1;
	// clear visit trace
	for (auto iter = adj_list.begin(); iter != adj_list.end(); iter++)
	{
		iter->first->visited = false;
		iter->first->id = iter - adj_list.begin();
	}
	// dfs
	list<DFS_Tree<_Data>*> forest;
	for (auto iter = adj_list.begin(); iter != adj_list.end(); iter++)
	{
		if (!iter->first->visited)
		{
			// added on
			DFS_Tree<_Data>* tree = new DFS_Tree<_Data>;
			tree->key = iter->first;
			tree->pi = nullptr;
			// old code
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
						// add a subtree
						DFS_Tree<_Data> *son = new DFS_Tree<_Data>;
						son->key = *adj_vertex;
						son->pi = tree;
						tree->son.push_back(son);
						tree = son;
						break;
					}
				}
				if (!has_adj_vetex)
				{
					// no adj vetices
					top->f = time++;
					visit_stack.pop();
					if (tree->pi != nullptr)
					{
						tree = tree->pi;
					}
				}
			}
			forest.push_back(tree);
		}
	}
	return forest;
}

// transpose the graph
template<class _Data>
vector<pair<Node<_Data>*, list<Node<_Data>*>>> 
transpose(const vector<pair<Node<_Data>*, list<Node<_Data>*>>> &adj_list)
{
	vector<pair<Node<_Data>*, list<Node<_Data>*>>> res(adj_list.size());
	for (unsigned i = 0; i < adj_list.size(); i++)
	{
		res[i].first = adj_list[i].first;
		for (auto iter = adj_list[i].second.begin(); iter != adj_list[i].second.end(); iter++)
		{
			res[(*iter)->id].second.push_back(const_cast<Node<_Data>*>(adj_list[i].first));
		}
	}
	return res;
}

template<class _Data>
list<DFS_Tree<_Data>*> strong_connected_component(const vector<pair<Node<_Data>*, list<Node<_Data>*>>> &adj_list)
{
	// copy to a new list
	vector<pair<Node<_Data>*, list<Node<_Data>*>>> adj_list_copy(adj_list.size());
	copy(adj_list.begin(), adj_list.end(), adj_list_copy.begin());

	// search for the first time to get Node.f
	dfs_search(adj_list_copy, _Data());
	// transpose the graph
	vector<pair<Node<_Data>*, list<Node<_Data>*>>> adj_list_transposed = transpose(adj_list_copy);
	// sort nodes by its f
	std::sort(adj_list_transposed.begin(), adj_list_transposed.end(), _Compare_F<_Data>());
	// dfs search again to get dfs tree
	list<DFS_Tree<_Data>*> forest = dfs_forest(adj_list_transposed);
	return forest;
}