///*1026*/
//#include <iostream>
//#include <vector>
//#include <string>
//#include <algorithm>
//#include <list>
//#include <queue>
//#include <set>
//#include <sstream>
// 
//using namespace std;
//
//
//class Node
//{
//public:
//    int x, y;
//    Node() :x(0), y(0){ }
//    Node(int x, int y) :x(x), y(y){ }
//};
//
//int main()
//{
//    int M, N;
//    short map[100][100];
//    short time[100][100];
//    bool visited[100][100];
//    char way[100][100];
//	vector<string> path_str;
//	path_str.reserve(100);
//    while(cin >> N >> M)
//    {
//        for(int i = 0; i < N; i++)
//        {
//            for(int j = 0; j < M; j++)
//            {
//                char c;
//                cin >> c;
//                if(c == '.')
//                {
//                    map[i][j] = 0;
//                }
//                else if(c == 'X')
//                {
//                    map[i][j] = -1;
//                }
//                else if(c <= '9' && c >= '1')
//                {
//                    map[i][j] = c - '0';
//                }
//                visited[i][j] = false;
//                way[i][j] = 0;
//                time[i][j] = map[i][j];
//            }
//        }
//        queue<Node> q;
//        visited[0][0] = true;
//		time[0][0] = 0;
//        q.push(Node(0, 0));
//        bool find_path = false;
//        while(!q.empty())
//        {
//            Node now_node = q.front();
//            q.pop();
//            // check all adj nodes
//            int x = now_node.x;
//            int y = now_node.y;
//            if(x == M - 1 && y == N - 1)
//            {
//                find_path = true;
//                break;
//            }
//            // check if has time
//            if(map[y][x] == 0)  // can go through this point
//            {
//                // check right
//                if(x < M - 1 && !visited[y][x + 1] && map[y][x + 1] != -1)
//                {
//                    q.push(Node(x + 1, y));
//                    visited[y][x + 1] = true;
//                    way[y][x + 1] = 'r';
//					time[y][x + 1] += 1 + time[y][x];
//                }
//                // check down
//                if(y < N - 1 && !visited[y + 1][x] && map[y + 1][x] != -1)
//                {
//                    q.push(Node(x, y + 1));
//                    visited[y + 1][x] = true;
//                    way[y + 1][x] = 'd';
//					time[y + 1][x] += 1 + time[y][x];
//                }
//                // check left
//                if(x > 0 && !visited[y][x - 1] && map[y][x - 1] != -1)
//                {
//                    q.push(Node(x - 1, y));
//                    visited[y][x - 1] = true;
//                    way[y][x - 1] = 'l';
//					time[y][x - 1] += 1 + time[y][x];
//                }
//                // check up
//                if(y > 0 && !visited[y - 1][x] && map[y - 1][x] != -1)
//                {
//                    q.push(Node(x, y - 1));
//                    visited[y - 1][x] = true;
//                    way[y - 1][x] = 'u';
//					time[y - 1][x] += 1 + time[y][x];
//                }
//            }
//            else    // wait and decrease value
//            {
//                map[y][x]--;
//                q.push(now_node);
//            }
//        }
//        if(find_path)
//        {
//            cout << "It takes " << time[N - 1][M - 1] << 
//				" seconds to reach the target position, let me show you the way." << endl;
//			// print path
//			int i = N - 1;
//			int j = M - 1;
//			int t;
//
//			while (i != 0 || j != 0)
//			{
//				t = time[i][j];
//				string s;
//				ostringstream ostr;
//				switch (way[i][j])
//				{
//				case 'd':
//					if(t - 1 == time[i - 1][j])
//						ostr << t << "s:(" << i - 1 << "," << j << ")->(" << i << ", " << j << ")\n";
//					else
//					{
//						ostr << time[i - 1][j] + 1 << "s:(" << i - 1 << "," << j << ")->(" << i << ", " << j << ")\n";
//						for (int tt = time[i - 1][j] + 2; tt <= t; tt++)
//						{
//							ostr << tt << "s:FIGHT AT (" << i << "," << j << ")\n";
//						}
//					}
//					i--;
//					break;
//				case 'r':
//					if (t - 1 == time[i][j - 1])
//						ostr << t << "s:(" << i << "," << j - 1 << ")->(" << i << ", " << j << ")\n";
//					else
//					{
//						ostr << time[i][j - 1] + 1 << "s:(" << i << "," << j - 1 << ")->(" << i << ", " << j << ")\n";
//						for (int tt = time[i][j - 1] + 2; tt <= t; tt++)
//						{
//							ostr << tt << "s:FIGHT AT (" << i << "," << j << ")\n";
//						}
//					}
//					j--;
//					break;
//				case 'l':
//					if (t - 1 == time[i][j + 1])
//						ostr << t << "s:(" << i << "," << j + 1 << ")->(" << i << ", " << j << ")\n";
//					else
//					{
//						ostr << time[i][j + 1] + 1 << "s:(" << i << "," << j + 1 << ")->(" << i << ", " << j << ")\n";
//						for (int tt = time[i][j + 1] + 2; tt <= t; tt++)
//						{
//							ostr << tt << "s:FIGHT AT (" << i << "," << j << ")\n";
//						}
//					}
//					j++;
//					break;
//				case 'u':
//					if (t - 1 == time[i + 1][j])
//						ostr << t << "s:(" << i + 1 << "," << j << ")->(" << i << ", " << j << ")\n";
//					else
//					{
//						ostr << time[i + 1][j] + 1 << "s:(" << i + 1 << "," << j << ")->(" << i << ", " << j << ")\n";
//						for (int tt = time[i + 1][j] + 2; tt <= t; tt++)
//						{
//							ostr << tt << "s:FIGHT AT (" << i << "," << j << ")\n";
//						}
//							
//					}
//					i++;
//					break;
//				}
//				s = ostr.str();
//				path_str.push_back(s);
//			}
//
//			for (auto iter = path_str.rbegin(); iter != path_str.rend(); iter++)
//			{
//				cout << *iter;
//			}
//			path_str.clear();
//        }
//        else
//        {
//            cout << "God please help our poor hero." << endl;
//        }
//        cout << "FINISH" << endl;
//    }
//    return 0;
//}