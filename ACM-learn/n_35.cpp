// 2544
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

#define INT_MAX 0xffffffff

using namespace std;

unsigned dijkstra(vector<vector<unsigned>> &graph)
{
    int n = graph.size();
    vector<bool> checked(n, false);
    vector<unsigned>dist(n, INT_MAX);

    checked[0] = true;
    
    for(int i = 0; i < n; i++)
    {
        dist[i] = graph[i][0];
    }

    int short_id, short_dist = INT_MAX;

    while(checked[n - 1])
    {
        for(int i = 1; i < n; i++)
        {
            if(!checked[i] && dist[i] < short_dist)
            {
                short_id = i;
                short_dist = dist[i];
            }
        }

        checked[short_id] = true;
        for(int i = 1; i < n; i++)
        {
            if(!checked[i] && graph[i][short_id] < INT_MAX)
            {
                dist[i] = min(short_dist + graph[i][short_id], dist[i]);
            }
        }
    }
    return dist[n - 1];
}

int main()
{
    int M, N;
    while(cin >> N >> M && M && N)
    {
        // graph initial
        vector<vector<unsigned>> graph(N);
        for(int i = 0; i < N; i++)
        {
            graph[i].resize(N, INT_MAX);
            graph[i][i] = 0;
        }
        // enter the graph
        int A, B, C;
        for(int i = 0; i < M; i++)
        {
            cin >> A >> B >> C;
            if(graph[A - 1][B - 1] > C)
            {
                graph[A - 1][B - 1] = C;
                graph[B - 1][A - 1] = C;
            }
        }
        int dist = dijkstra(graph);
        cout << dist << endl;
    }
}


/*
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#define INF 1000000
using namespace std;
int city,road;
int mapp[205][205];
int spand[205];
int select[205];
void dij(int city)
{
    int minn,k,i,j;
    memset(select,0,sizeof(select));
    for(i=1;i<=city;i++)
    spand[i]=mapp[1][i];
    spand[1]=0;select[1]=1;
    for(i=2;i<=city;i++)
    {
        minn=INF;k=-1;
        for(j=1;j<=city;j++)
        {
            if(!select[j]&&spand[j]<minn)
            {
                k=j;minn=spand[j];
            }
        }
        if(k==-1)break;
        select[k]=1;
        for(j=1;j<=city;j++)
        {
            if(spand[j]>spand[k]+mapp[k][j]&&!select[j])
            spand[j]=spand[k]+mapp[k][j];
        }
    }
    printf("%d\n",spand[city]);
}
int main()
{
    int i;int x,y,z;
    while(scanf("%d%d",&city,&road)!=EOF)
    {
        if(city==0||road==0)
        break;
        memset(mapp,INF,sizeof(mapp));
        memset(spand,INF,sizeof(spand));
        for(i=1;i<=road;i++)
        {
            scanf("%d%d%d",&x,&y,&z);
            if(mapp[x][y]>z||mapp[y][x]>z)
            {
                mapp[x][y]=z;mapp[y][x]=z;
            }
        }
        dij(city);
    }
    return 0;
}
 */