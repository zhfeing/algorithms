//2593
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;
#define MAX_NUMBER 100000

int res_1[MAX_NUMBER];
int res_2[MAX_NUMBER];

int main()
{
    int N;
    int a[MAX_NUMBER];
    while(cin >> N && N != 0)
    {
        int dp[MAX_NUMBER];
        scanf("%d", &dp[0]);
        res_1[0] = dp[0];
        for(int i = 1; i < N; i++)
        {
            scanf("%d", &a[i]);
            dp[i] = max(0, dp[i - 1]) + a[i];
            res_1[i] = max(res_1[i - 1], dp[i]);
        }
        res_2[N - 1] = a[N - 1];
        int max_sum = res_2[N - 1] + res_1[N - 2];
        for(int i = N - 2; i > 0; i--)
        {
            res_2[i] = max(0, res_2[i + 1]) + a[i];
            max_sum = max(max_sum, res_2[i] + res_1[i - 1]);
        }
        cout << max_sum << endl;
    }
    return 0;
}