/*1016*/
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

set<int> PrimeSet = { 1, 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, };


vector<int> number_used_stack;
int N;


inline bool isPrime(const int &a, const int &b)
{
	return PrimeSet.find(a + b) != PrimeSet.end();
}
inline bool find_in_vector(const int &index)
{
	for (vector<int>::iterator iter = number_used_stack.begin(); 
		iter != number_used_stack.end(); iter++)
	{
		if (*iter == index)
			return true;
	}
	return false;
}

void print_circle(const int & layer)
{
	if (N == layer)
	{
		if (isPrime(1, number_used_stack[layer - 1]))
		{
			for (vector<int>::iterator iter = number_used_stack.begin();
				iter != number_used_stack.end(); iter++)
			{
				cout << (*iter);
				if (iter != number_used_stack.end() - 1)
					cout << " ";
			}
			cout << endl;
		}
		return;
	}
	for (int i = 2; i <= N; i++)
	{
		if (!find_in_vector(i) && isPrime(number_used_stack[layer - 1], i))
		{
			number_used_stack.push_back(i);
			print_circle(layer + 1);
			number_used_stack.pop_back();
		}
	}
}

int main()
{
	int n;
	int index = 1;
	number_used_stack.reserve(20);
	while (cin >> n)
	{
		N = n;
		cout << "Case " << index++ << ":" << endl;
		number_used_stack.push_back(1);
		print_circle(1);
		number_used_stack.clear();
		cout << endl;
	}
}

#include <cstdio>  
#include <cstring>  
#include <iostream>
using namespace std;

bool vis[50], prime[50];

bool is_prime(int n)
{
	for (int i = 2; i*i <= n; i++)
		if (!(n % i))
			return 0;
	return 1;
}
void init()
{
	for (int i = 0; i < 50; i++)
		prime[i] = is_prime(i);
}

void dfs(int *A, int cur, int n)
{
	if (cur == n && prime[A[0] + A[n - 1]])
	{
		printf("%d", A[0]);
		for (int i = 1; i < n; i++)
			printf(" %d", A[i]);
		printf("\n");
	}
	else
	{
		for (int i = 2; i <= n; i++)
		{
			if (!vis[i] && prime[i + A[cur - 1]])
			{
				A[cur] = i;
				vis[i] = 1;
				dfs(A, cur + 1, n);
				vis[i] = 0;
			}
		}
	}
}

int main()
{
	init();
	//    freopen("input.txt","r",stdin);  
	memset(vis, 0, sizeof(vis));
	int A[30] = { 1 };
	int N;
	int nCase = 1;
	while (cin>>N)
	{
		/*
		if (nCase > 1)
		printf("\n");
		*/
		printf("Case %d:\n", nCase++);
		dfs(A, 1, N);
		printf("\n");
	}
}