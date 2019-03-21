// check sum
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    string s;
    while(true)
    {
        getline(cin, s);
        if(s[0] == '#')
            break;
        int sum = 0;
        for(int i = 0; i < s.size(); i++)
        {
            if(s[i] == ' ')
                continue;
            sum += (i + 1)*(s[i] - 'A' + 1);
        }
        cout << sum << endl;
    }
    return 0;
}