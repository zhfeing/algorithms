#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <stack>
#include "dfs.hpp"
#include "dfs_applications.hpp"

using namespace std;

int main()
{
	int n;
	vector<Node<int>*> nodes;
	vector<vector<bool>> adj_matrix;
	nodes.reserve(1000);
	adj_matrix.reserve(1000);
	for (auto iter = adj_matrix.begin(); iter != adj_matrix.end(); iter++)
	{
		iter->reserve(1000);
	}
	cout << "enter number n" << endl;
	while (cin >> n)
	{
		if (n <= 0)
		{
			break;
		}
		else if(n > 1000)
		{
			cout << "n is too big";
			continue;
		}
		nodes.resize(n);
		adj_matrix.resize(n);
		for (auto iter_i = adj_matrix.begin(); iter_i != adj_matrix.end(); iter_i++)
		{
			iter_i->resize(n);
		}
		// enter the adj matrix
		cout << "enter the adj matrix" << endl;
		bool adj;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				cin >> adj;
				adj_matrix[i][j] = adj;
			}
		}
		cout << "enter node value" << endl;
		int data;
		for (auto iter = nodes.begin(); iter != nodes.end(); iter++)
		{
			cin >> data;
			(*iter) = new Node<int>;
			(*iter)->data = new int(data);
			(*iter)->id = iter - nodes.begin();
		}

		int k;
		cout << "enter key" << endl;
		cin >> k;
		vector<pair<Node<int>*, list<Node<int>*>>> adj_list;
		adj_list = adj_matrix2list<int>(nodes, adj_matrix);

		// list<Node<int>*> res1 = dfs_search<int>(nodes, adj_matrix, k);
		list<Node<int>*> res2 = dfs_search<int>(adj_list, k);

		list<DFS_Tree<int>*> forest = strong_connected_component<int>(adj_list);
		
		for (auto iter_i = adj_matrix.begin(); iter_i != adj_matrix.end(); iter_i++)
		{
			iter_i->clear();
		}
		adj_matrix.clear();
		for (auto iter = nodes.begin(); iter != nodes.end(); iter++)
		{
			delete *iter;
		}
	}
	return 0;
}