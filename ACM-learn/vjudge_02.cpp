// B - Goldbach's Conjecture 
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

bool check_prime(int n)
{
    if(n == 2 || n == 1 || n == 3)
    {
        return true;
    }
    for(int i = 2; i <= sqrt(n); i++)
    {
        if(n % i == 0)
        {
            return false;
        }
    }
    return true;
}

int main()
{
    int n;
    while(cin >> n && n != 0)
    {
        bool found = false;
        for(int i = 3; i <= n/2; i++)
        {
            if(check_prime(i) && check_prime(n - i))
            {
                cout << n << " = " << i << " + " << n - i << endl;
                found = true;
                break;
            }            
        }
        if(!found)
        {
            cout << "Goldbach's conjecture is wrong." << endl;
        }
    }
    return 0;
}