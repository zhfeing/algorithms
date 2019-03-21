#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <functional>

using namespace std;

typedef vector<int> Vint;

Vint add(const Vint &a, const Vint &b)
{
    Vint result(max(a.size(), b.size()));
    if(a.size() > b.size())
    {
        int c = 0;
        for(int i = 0; i < b.size(); i++)
        {
            result[i] = (a[i] + b[i] + c)%10;
            c = (a[i] + b[i] + c)/10;
        }
        for(int i = b.size(); i < a.size(); i++)
        {
            result[i] = (a[i] + c)%10;
            c = (a[i] + c)/10;
        }
        if(c != 0)
        {
            result.push_back(c);
        }
    }
    else
    {
        int c = 0;
        for(int i = 0; i < a.size(); i++)
        {
            result[i] = (a[i] + b[i] + c)%10;
            c = (a[i] + b[i] + c)/10;
        }
        for(int i = a.size(); i < b.size(); i++)
        {
            result[i] = (b[i] + c)%10;
            c = (b[i] + c)/10;
        }
        if(c != 0)
        {
            result.push_back(c);
        }
    }
    return result;
}

int main()
{
    string s;
    Vint sum(1, 0);
    while(cin >> s)
    {
        size_t length = s.length();
        if(length == 1 && s[0] == '0')
        {
            break;
        }
        Vint a(length);
        for(int i = 0; i < length; i++)
        {
            a[length - i - 1] = s[i] - '0';
        }
        sum = add(sum, a);
    }
    for(int i = sum.size() - 1; i >= 0; i--)
    {
        cout << sum[i];
    }
    cout << endl;
    //getchar(); getchar();
    return 0;
}