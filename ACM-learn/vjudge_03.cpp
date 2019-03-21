// // C - Moving Tables 
// #include <iostream>
// #include <string>
// #include <vector>
// #include <algorithm>
// #include <cmath>

// using namespace std;

// struct ST
// {
//     int s;
//     int t;
// };

// struct Pr
// {
//     bool operator()(const ST &lhs, const ST &rhs)
//     {
//         if(lhs.t < rhs.t)
//             return true;
//         else if(lhs.t > rhs.t)
//             return false;
//         else
//         {
//             return lhs.s < rhs.s;
//         }
//     }
// };

// typedef vector<ST> Vst;
// typedef vector<bool> Vbool;


// void greedy(const Vst &st, Vbool &visit, int begin, const int N)
// {
//     if(begin >= N)
//         return;
//     bool found = false;
//     int i;
//     for(i = begin + 1; i < N; i++)
//     {
//         if(visit[i])
//         {
//             continue;
//         }
//         if(st[i].s > st[begin].t)
//         {
//             found = true;
//             break;
//         }
//     }
//     if(found)
//     {
//         visit[i] = true;
//         greedy(st, visit, i, N);
//     }
// }

// int main()
// {
//     int T;
//     cin >> T;
//     Vst st;
//     st.reserve(200);
//     while(T--)
//     {
//         int N;
//         cin >> N;
//         st.resize(N);
//         int s, t;
//         for(int i = 0; i < N; i++)
//         {
//             cin >> s >> t;
//             if(s > t)
//             {
//                 int temp = s;
//                 s = t;
//                 t = temp;
//             }
//             st[i].s = (s - 1)/2;
//             st[i].t = (t - 1)/2;
//         }

//         sort(st.begin(), st.end(), Pr());

//         cout << endl << endl;
//         for(int i = 0; i < N; i++)
//         {
//             cout << st[i].s << " " << st[i].t << endl;
//         }

//         Vbool visit(N, false);
//         int pairs = 0;
//         for(int i = 0; i < N; i++)
//         {
//             if(visit[i])
//                 continue;
//             visit[i] = true;
//             greedy(st, visit, i, N);
//             pairs++;
//         }

//         // for(int i = 0; i < N; i++)
//         // {
//         //     cout << visit[i];
//         // }
//         // cout << endl;
//         cout << 10*pairs << endl;
//         st.clear();
//     }
//     return 0;
// }




#include <iostream>
using namespace std;
 
struct table{
	int front,back;
	bool use;
}tb[10001];
 
 
int main()
{
	int T,N,total;			//T为有几组数据，N为每组数据有几行数据,total为总用时
	int i,j,temp;			
	table tem;
 
	cin>>T;
	while(T--)
	{
		//**************************   输入
		cin>>N;
		for(i=0;i<N;++i)
		{
			cin>>tb[i].front>>tb[i].back;
 
			if(tb[i].front%2==1)
				tb[i].front+=1;
			if(tb[i].back%2==1)
				tb[i].back+=1;
 
			if(tb[i].front>tb[i].back)
			{
				temp=tb[i].front;
				tb[i].front=tb[i].back;
				tb[i].back=temp;
			}
		
			tb[i].use=true;
		}
		//*************************	   排序
 
		for(i=0;i<N-1;++i)
			for(j=i+1;j<N;++j)
				if(tb[i].front>tb[j].front)
				{
					tem=tb[i];
					tb[i]=tb[j];
					tb[j]=tem;
				}
 
		//*************************	   计算值
		total=0;
		for(i=0;i<N;++i)
		{
			if(tb[i].use==false)
				continue;
			
			temp=tb[i].back;
 
			for(j=i+1;j<N;++j)
			{
				if(tb[j].use==false)
					continue;
				if(tb[j].front>temp)
				{
					tb[j].use=false;
					temp=tb[j].back;
				}
			}
			
			total+=10;
		}
		
 
		//*************************     输出
		cout<<total<<endl;
		
 
	}
 
	return 0;
}