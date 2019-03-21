#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <random>
#include <ctime>
#include <numeric>

using namespace std;

using Point = pair<float, float>;
using Paramater = Point;    // (k, b)
using Module = vector<Point>;

double gaussrand()
{
    static double V1, V2, S;
    static int phase = 0;
    double X;

    if ( phase == 0 ) {
        do {
            double U1 = (double)rand() / RAND_MAX;
            double U2 = (double)rand() / RAND_MAX;

            V1 = 2 * U1 - 1;
            V2 = 2 * U2 - 1;
            S = V1 * V1 + V2 * V2;
        } while(S >= 1 || S == 0);

        X = V1 * sqrt(-2 * log(S) / S);
    } else
        X = V2 * sqrt(-2 * log(S) / S);

    phase = 1 - phase;

    return X;
}
Module create_module(size_t size, float k, float b, float x_min, float x_max, float var)
{
    Module m(size);
    float x, y;
    for(auto iter = m.begin(); iter != m.end(); iter++)
    {
        x = rand()/(float)RAND_MAX*(x_max - x_min) + x_min;
        y = k*x + b + gaussrand()*var;
        *iter = Point(x, y);
    }
    return m;
}
ostream &operator <<(ostream &out, const Point &p)
{
    out << "(" << p.first << ", " << p.second << ")";
    return out;
}

double distance(float k, float b, const Point &p)
{
    double num = fabs(k*p.first - p.second + b);
    double den = sqrt(k*k + 1);
    return num/den;
}

double get_fittness(const Module &m, size_t index_1, size_t index_2)
{
    double fit = 0;
    Point p1 = m[index_1];
    Point p2 = m[index_2];
    float k = (p2.second - p1.second)/(p2.first - p1.first);
    float b = p1.second - k*p1.first;
    for(size_t i = 0; i < m.size(); i++)
    {
        fit += distance(k, b, m[i]);
    }
    return fit;
}

Paramater get_parameter_of_line(const Point &p1, const Point &p2)
{
    float k = (p2.second - p1.second)/(p2.first - p1.first);
    float b = p1.second - k*p1.first;
    return Paramater(k, b);
}

Paramater ransac(const Module &m)
{
    constexpr int RepeatTimes = 1000;
    size_t size = m.size();

    Paramater p;
    double fittness = numeric_limits<double>::max();  // the lower the better

    for (int i = 0; i < RepeatTimes; i++)
    {
        // random choose two different points
        int index_1, index_2;
        index_1 = rand()%size;
        index_2 = rand()%size;
        if(index_1 == index_2)
        {
            i--;    // this time does not account
            continue;
        }
        float new_fittness = get_fittness(m, index_1, index_2);
        if(fittness > new_fittness)
        {
            fittness = new_fittness;
            p = get_parameter_of_line(m[index_1], m[index_2]);
        }
    }
    return p;
}
Paramater hough_transform(const Module &m)
{
    // set up table
    int table[200][200] = {0};
    float x, y;
    float k_f, b_f;
    int b;
    for(auto iter = m.begin(); iter != m.end(); iter++)
    {
        x = iter->first;
        y = iter->second;
        for(int k = 0; k < 200; k++)
        {
            k_f = k/10.0 - 10;
            b_f = -x*k_f + y;
            b = int((b_f + 10)*10 + 0.5);   // round
            if(b >= 0 && b <200)
            {
                table[b][k]++;
            }
        }
    }
    Paramater p(-10, -10);
    int max_ele = table[0][0];
    for(int i = 0; i < 200; i++)
    {
        for(int j = 0; j < 200; j++)
        {
            if(table[i][j] > max_ele)
            {
                max_ele = table[i][j];
                p.second = i/10.0 - 10;
                p.first = j/10.0 - 10;
            }
        }
    }
    return p;
}
int main()
{
    for(int i = 0; i < 10; i++)
    {
        Module m = create_module(50000, 2, 1, 0, 10, 1);

    //    for(auto iter = m.begin(); iter != m.end(); iter++)
    //    {
    //        cout << *iter << endl;
    //    }
        Paramater res = ransac(m);
        cout << "ransac\t" << res << endl;
        res = hough_transform(m);
        cout << "hough\t" << res << endl;
    }

    return 0;
}
