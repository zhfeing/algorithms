#include "graph.hpp"
using namespace std;
int main()
{
	while (true)
	{
		cout << "enter vertices number" << endl;
		int num;
		cin >> num;
		Graph_matrix graph(num);
		graph.setup_from_input();
		int index;
		cout << "enter index to find" << endl;
		cin >> index;
		int res = graph.search_bfs(index);
		if (res >= 0)
			cout << "find" << endl;
		else
			cout << "not find" << endl;
	}
	return 0;
}
