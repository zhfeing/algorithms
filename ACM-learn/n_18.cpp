///*1010*/
//#define _CRT_SECURE_NO_WARNINGS
//#include <iostream>
//#include <cassert>
//#include <vector>
//#include <string>
//#include <cmath>
//#include <algorithm>
//#include <list>
//#include <queue>
//#include <set>
//#include <cstdlib>
//#include <cmath>
//
//using namespace std;
//class Point
//{
//public:
//	int x, y;
//	Point(int x, int y) : x(x), y(y)
//	{ }
//};
//
//#define MAX_SIZE 6
//
//int S_x, S_y, D_x, D_y;
//int N, M, T;
//char maze[MAX_SIZE][MAX_SIZE];
//bool maze_visited[MAX_SIZE][MAX_SIZE];
//
//bool flag = false;
//
//void dfs(int layer, int x, int y)
//{
//	if (layer == T)
//	{
//		if (x == D_x && y == D_y)
//		{
//			flag = true;
//			return;
//		}
//		else
//		{
//			flag = false;
//			return;
//		}
//	}
//
//	maze_visited[y][x] = true;
//	// search by up left down right order
//	// search up
//	if (y > 0 && ((maze[y - 1][x] == '.' && !maze_visited[y - 1][x]) || 
//		(maze[y - 1][x] == 'D' && layer == T - 1)))
//	{
//		dfs(layer + 1, x, y - 1);
//		if (flag == true)
//			return;
//	}
//	// search left
//	if (x > 0 && ((maze[y][x - 1] == '.' && !maze_visited[y][x - 1]) ||
//		(maze[y][x - 1] == 'D' && layer == T - 1)))
//	{
//		dfs(layer + 1, x - 1, y);
//		if (flag == true)
//			return;
//	}
//	// search down
//	if (y < N - 1 && ((maze[y + 1][x] == '.' && !maze_visited[y + 1][x]) ||
//		(maze[y + 1][x] == 'D' && layer == T - 1)))
//	{
//		dfs(layer + 1, x, y + 1);
//		if (flag == true)
//			return;
//	}
//	// search right
//	if (x < M - 1 && ((maze[y][x + 1] == '.' && !maze_visited[y][x + 1]) ||
//		(maze[y][x + 1] == 'D' && layer == T - 1)))
//	{
//		dfs(layer + 1, x + 1, y);
//		if (flag == true)
//			return;
//	}
//	maze_visited[y][x] = false;
//}
//
//int main()
//{
//	while (cin >> N >> M >> T)
//	{
//		if (N == 0 && M == 0 && T == 0)
//		{
//			break;
//		}
//		// initial
//		for (int i = 0; i < MAX_SIZE; i++)
//		{
//			for (int j = 0; j < MAX_SIZE; j++)
//			{
//				maze_visited[i][j] = false;
//			}
//		}
//		// input process
//		for (int i = 0; i < N; i++)
//		{
//			char c;
//			for (int j = 0; j < M; j++)
//			{
//				cin >> c;
//				maze[i][j] = c;
//				if (c == 'S')
//				{
//					S_x = j;
//					S_y = i;
//				}
//				else if (c == 'D')
//				{
//					D_x = j;
//					D_y = i;
//				}
//			}
//		}
//		// using dfs algorithm
//		int dis = abs(S_x - D_x) + abs(S_y - D_y);
//		if (dis > T || (dis + T) % 2 == 1)
//		{
//			cout << "NO" << endl;
//			continue;
//		}
//		dfs(0, S_x, S_y);
//		if (flag)
//		{
//			cout << "YES" << endl;
//		}
//		else
//		{
//			cout << "NO" << endl;
//		}
//		flag = false;
//	}
//	return 0;
//}

