#include <vector>
#include <queue>
#include <cassert>
#include <iostream>
#include <algorithm>
#include <list>
#include <string>
#include <memory>


using namespace std;

class Graph_matrix
{
public:
	typedef vector<int>::iterator Vint_iter;
	typedef vector<vector<bool>> Vbool_2d;
	typedef vector<int> Vint;
	Graph_matrix(int vertices);
	~Graph_matrix();
	void setup_from_input();
	int search_dfs(int);
	int search_bfs(int);
private:
	Vbool_2d *graph_matrix;
	Vint *vertex;
	int vertices;
	int _DFS(int index, int vertex_id, vector<bool> &);
};

Graph_matrix::Graph_matrix(int vertices)
{
	this->vertices = vertices;
	graph_matrix = new Vbool_2d(vertices);
	for (auto iter = graph_matrix->begin(); iter != graph_matrix->end(); iter++)
	{
		iter->resize(vertices, false);
	}
	vertex = new Vint(vertices);
}
Graph_matrix::~Graph_matrix()
{
	delete graph_matrix;
	delete vertex;
}
void Graph_matrix::setup_from_input()
{
	cout << "type in graph matrix" << endl;
	bool b;
	for (auto iter_r = graph_matrix->begin(); iter_r != graph_matrix->end(); iter_r++)
	{
		for (auto iter_c = iter_r->begin(); iter_c != iter_r->end(); iter_c++)
		{
			cin >> b;
			*iter_c = b;
		}
	}
	cout << "type in element" << endl;
	for (auto iter = vertex->begin(); iter != vertex->end(); iter++)
	{
		cin >> *iter;
	}
}
int Graph_matrix::search_dfs(int element)
{
	vector<bool> buffer_record_visited(vertices, false);
	for (int i = 0; i < vertices; i++)
	{
		if (!buffer_record_visited[i])
		{
			int res = _DFS(element, i, buffer_record_visited);
			if (res >= 0)
				return vertex->at(res);
		}
	}
	return -1;
}
int Graph_matrix::search_bfs(int element)
{
	typedef pair<int, int> MyPair;	// (value, index)
	queue<MyPair> q;
	vector<bool> visit_buffer(vertices, false);
	q.push(MyPair(vertex->at(0), 0));
	visit_buffer[0] = true;
	while (!q.empty())
	{
		MyPair vertex = q.front();
		q.pop();
		if (vertex.first == element)
		{
			return vertex.second;
		}
		for (int i = 0; i < vertices; i++)
		{
			if (!visit_buffer[i] && graph_matrix->at(vertex.second)[i])		
				// not visited and adj to this vertex
			{
				q.push(MyPair(this->vertex->at(i), i));
			}
		}
		visit_buffer[vertex.second] = true;
	}
	return -1;
}

int Graph_matrix::_DFS(int index, int vertex_id, vector<bool> &buffer)
{
	buffer[vertex_id] = true;
	if (vertex->at(vertex_id) == index)
	{
		return vertex_id;
	}
	for (int i = 0; i < vertices; i++)
	{
		if (graph_matrix->at(vertex_id)[i] == true && !buffer[i])
			// node connected with vertex_id and not visited
		{
			int res = _DFS(index, i, buffer);
			if (res >= 0)
			{
				return res;
			}
		}
	}
	return -1;
}