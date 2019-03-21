#include <iostream>
#include <cmath>
#include <vector>
#include <cassert>
typedef std::vector<double> Vdouble;

const double e = 2.7181218;

double f(double x);//the function
double integrate_simpson(double a, double b, double (*function)(double));
int getNodeNum(double a, double b, double(*function)(double));
int main()
{
	printf("%.15lf\n", integrate_simpson(0, 5, f));
}
double f(double x)
{
	return exp(x);
}
double integrate_simpson(double a, double b, double (*function)(double))
{
	int N = getNodeNum(a, b, function);
	std::cout << N << std::endl;
	assert(N > 1);
	double step = (b - a) / (N - 1);
	Vdouble funcValueList(N);
	for (int i = 0; i < N; i++)
		funcValueList[i] = function(a + i*step);
	double integral;
	integral = funcValueList[0] + funcValueList[N - 1];
	for (int i = 1; i < N-1; i++)
	{
		if (i % 2 == 1)
		{
			integral += 4 * funcValueList[i];
		}
		else
		{
			integral += 2 * funcValueList[i];
		}
	}
	integral *= step / 3.0;
	return integral;
}
int getNodeNum(double a, double b, double (*function)(double))
{
	/*error = abs((b-a)*step^4*f[4](x0)/2880)*/
	const double epsilone = 0.5e-14;
	int nodeNumber;
	nodeNumber = ceil(2 * (b - a) * (pow(epsilone * 2880 / e / (b - a), -0.25) * 2 + 1) + 1);
	if (nodeNumber % 2 == 0)
		nodeNumber++;
	return nodeNumber;
}
