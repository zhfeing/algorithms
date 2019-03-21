/*1728*/
#include <iostream>
#include <cassert>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <list>
#include <queue>
#include <set>
#include <cstdlib>
#include <cmath>

using namespace std;

// using bfs
typedef struct Vertex
{
	Vertex(int x, int y, int turn, int last_dir)
		:x(x), y(y), turn(turn), last_dir(last_dir)
	{
	}
	int x, y;
	int turn, last_dir;
}Vertex;


string find_path(const vector<string> &maze, int k, int x1, int y1, int x2, int y2, int m, int n)
{
	x1--;
	y1--;
	x2--;
	y2--;
	vector<vector<unsigned short>> visited_table(m);	// 0000,0000 low 4 bits are up, left, down, right
	const unsigned short UP = 0x08;
	const unsigned short LEFT = 0x04;
	const unsigned short DOWN = 0x02;
	const unsigned short RIGHT = 0x01;
	const unsigned short ALL_DIRECTION = 0x0f;
	for (auto iter = visited_table.begin(); iter != visited_table.end(); iter++)
	{
		iter->resize(n, 0);
	}
	queue<Vertex> q;
	q.push(Vertex(x1, y1, -1, 0));
	while (!q.empty())
	{
		Vertex now_point = q.front();
		q.pop();
		int x = now_point.x;
		int y = now_point.y;
		int turn_count = now_point.turn;
		int last_dir = now_point.last_dir;

		if (x == x2 && y == y2 && now_point.turn <= k)
		{
			return "yes";
		}
		
		if (turn_count > k || (visited_table[y][x] & ALL_DIRECTION) == ALL_DIRECTION)
		{
			continue;
		}

		visited_table[y][x] = ALL_DIRECTION;
		// enumerate adj vertices
		for (int dir = 1; dir <= 4; dir++)
		{
			Vertex next_vertex(0, 0, 0, 0);
			int i;
			switch (dir)
			{
			case 1:		// check direct up
				i = y - 1;
				// go stright up
				while (i >= 0 && maze[i][x] == '.' && !(visited_table[i][x] & UP))
					// not reach upper bound and maze at that point is '.' and not visited
				{
					next_vertex.x = x;
					next_vertex.y = i;
					next_vertex.last_dir = dir;
					next_vertex.turn = turn_count + 1;
					visited_table[i][x] |= UP;
					q.push(next_vertex);
					i--;
				}
				break;
			case 2:		// check direct left
				i = x - 1;
				while (i >= 0 && maze[y][i] == '.' && !(visited_table[y][i] & LEFT))
					// not reach left bound and maze at that point is '.' and not visited
				{
					next_vertex.x = i;
					next_vertex.y = y;
					next_vertex.last_dir = dir;
					next_vertex.turn = turn_count + 1;
					visited_table[y][i] |= LEFT;
					q.push(next_vertex);
					i--;
				}				
				break;
			case 3:		// check direct down
				i = y + 1;
				while (i < m && maze[i][x] == '.' && !(visited_table[i][x] & DOWN))
					// not reach lower bound and maze at that point is '.' and not visited
				{
					next_vertex.x = x;
					next_vertex.y = i;
					next_vertex.last_dir = dir;
					next_vertex.turn = turn_count + 1;
					visited_table[i][x] |= DOWN;
					q.push(next_vertex);
					i++;
				}
				break;
			case 4:		// check direct right
				i = x + 1;
				while (i < n && maze[y][i] == '.' && !(visited_table[y][i] & RIGHT))
					// not reach right bound and maze at that point is '.' and not visited
				{
					next_vertex.x = i;
					next_vertex.y = y;
					next_vertex.last_dir = dir;
					next_vertex.turn = turn_count + 1;
					visited_table[y][i] |= RIGHT;
					q.push(next_vertex);
					i++;
				}
				break;
			default:
				break;
			}
		}
	}
	return "no";
}

int main()
{
	int t;
	cin >> t;
	while (t--)
	{
		int m, n;
		cin >> m >> n;
		vector<string> maze(m);
		for (int i = 0; i < m; i++)
		{
			cin >> maze[i];
		}
		int k, x1, y1, x2, y2;
		cin >> k >> x1 >> y1 >> x2 >> y2;
		cout << find_path(maze, k, x1, y1, x2, y2, m, n) << endl;
	}
	//getchar();
	//getchar();
	//getchar();
	//getchar();
	//getchar();
	return 0;
}