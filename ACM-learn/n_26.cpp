///*1074*/
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
//
//typedef vector<string> VString;
//typedef vector<unsigned> VUnsigned;
//
//class State
//{
//public:
//	State()
//	{
//		time_cost = 0;
//		score = UINT32_MAX;
//		last_state = 0x0;
//	}
//	State(unsigned time_cost, unsigned score, unsigned last_state)
//		:time_cost(time_cost), score(score), last_state(last_state){ }
//	unsigned time_cost, score, last_state;
//};
//
//int main()
//{
//	int T;
//	cin >> T;
//	vector<State> dp;
//	dp.reserve(0x1<<15 - 1);	// 2^15 - 1
//	while (T--)
//	{
//		int N;
//		cin >> N;
//		VString S(N);
//		VUnsigned C(N);
//		VUnsigned D(N);
//		dp.resize(1 << N);
//		for (int i = 0; i < N; i++)
//		{
//			cin >> S[i] >> D[i] >> C[i];
//		}
//		dp[0].score = 0;
//		for (unsigned state = 0x1; state < (1 << N); state++)
//		{
//			// enum all the task that can be done to get to this state
//			for (int id = 0; id < N; id++)
//			{
//				unsigned now_time;
//				if (state & (0x1 << id))		
//					// task id has been done, namely, state can transform from last state
//				{
//					unsigned last_state = state & ~(0x1 << id);
//					now_time = dp[last_state].time_cost + C[id];
//
//					// all tasks over deadline should have score
//					unsigned score_this_time = 0;
//					for (unsigned task = 0; task < N; task++)
//					{
//						if (D[task] < now_time && (~last_state & (0x1 << task)))
//							// task has not been done and over the deadline
//						{
//							unsigned tmp = now_time - D[task];
//							if (tmp > C[id])
//								tmp = C[id];
//							score_this_time += tmp;
//						}
//					}
//					if (dp[state].score >= dp[last_state].score + score_this_time)
//						// find a more fast path
//					{
//						dp[state].last_state = last_state;
//						dp[state].score = score_this_time + dp[last_state].score;
//						dp[state].time_cost = now_time;
//					}
//				}
//			}
//		}
//
//		cout << dp.back().score << endl;
//
//		unsigned state = (1 << N) - 1;
//		vector<string> state_list;
//		while (state)
//		{
//			unsigned i = 0;
//			while ((0x1 << i++) != (state ^ dp[state].last_state))
//				;
//			state_list.push_back(S[i - 1]);
//			state = dp[state].last_state;
//		}
//		for (vector<string>::reverse_iterator r_iter = state_list.rbegin(); 
//			r_iter != state_list.rend(); r_iter++)
//		{
//			cout << *r_iter << endl;
//		}
//		dp.clear();
//	}
//}
