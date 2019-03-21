// 3299
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

double calculate_t(double d, double h)
{
    double e = 6.11*exp(5417.7530*(1.0/273.16 - 1.0/(d + 273.16)));
    return h - 0.5555*(e - 10);
}
double calculate_d(double t, double h)
{
    double e = (h - t)/0.5555 + 10;
    return 1.0/(1.0/273.16 - log(e/6.11)/5417.7530) - 273.16;
}
double calculate_h(double t, double d)
{
    double e = 6.11*exp(5417.7530*(1.0/273.16 - 1.0/(d + 273.16)));
    return t + 0.5555*(e - 10);
}

int main()
{
    char c1, c2;
    double t, d, h;
    while (cin >> c1 && c1 != 'E')
    {
        double n1, n2;
        cin >> n1 >> c2 >> n2;
        switch(c1)
        {
        case 'T':
            t = n1;
            switch(c2)
            {
            case 'D':
                d = n2;
                h = calculate_h(t, d);
                break;
            case 'H':
                h = n2;
                d = calculate_d(t, h);
                break;
            }
            break;
        case 'D':
            d = n1;
            switch(c2)
            {
            case 'T':
                t = n2;
                h = calculate_h(t, d);
                break;
            case 'H':
                h = n2;
                t = calculate_t(d, h);
                break;
            }
            break;
        case 'H':
            h = n1;
            switch(c2)
            {
            case 'T':
                t = n2;
                d = calculate_d(t, h);
                break;
            case 'D':
                d = n2;
                t = calculate_t(d, h);
                break;
            }
            break;
        }
        printf("T %.1f D %.1f H %.1f\n", t, d, h);
    }
    return 0;
}