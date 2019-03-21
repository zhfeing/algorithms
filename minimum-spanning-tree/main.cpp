#include "mst.hpp"
#include "graph.hpp"

using namespace std;
using namespace zhf_lib;

int main()
{
	size_t size;
	cout << "enter size" << endl;
	while (cin >> size)
	{
		if (size <= 0)
		{
			break;
		}
		vector<int> nodes_data(size);
		vector<vector<bool>> adj_matrix(size);
		vector<vector<WeightedEdge<unsigned>>> edge_weight(size);
		
		cout << "enter data" << endl;
		for (auto iter = nodes_data.begin(); iter != nodes_data.end(); iter++)
		{
			cin >> *iter;
		}
		cout << "enter adj matrix" << endl;
		for (auto i = adj_matrix.begin(); i != adj_matrix.end(); i++)
		{
			i->resize(size);
			for (auto j = i->begin(); j != i->end(); j++)
			{
				bool b;
				cin >> b;
				*j = b;
			}
		}
		cout << "enter weight matrix" << endl;
		for (auto i = edge_weight.begin(); i != edge_weight.end(); i++)
		{
			i->resize(size);
			for (auto j = i->begin(); j != i->end(); j++)
			{
				unsigned b;
				cin >> b;
				*j = b;
			}
		}
		WeightedGraphMatrix<int, MST_GraphNode<int>, WeightedEdge<unsigned>> 
			g2(size, nodes_data, adj_matrix, edge_weight);
		
		MST_GraphNode<int> *r1 = MST(g2);
		/*WeightedGraphList<int, MST_GraphNode<int>, WeightedEdge<unsigned>>
			g1(size, nodes_data, adj_matrix, edge_weight);
		MST_GraphNode<int> *r2 = MST(g1);*/
		cout << "enter size" << endl;
	}
	return 0;
}
