#include <cstdio>
#include <cmath>
#include <vector>
#include <string>
#include <map>
#include <cassert>
using namespace std;
namespace SimpleLinearIteration
{
	bool findZeros(double& ans);
	double iterationFunction();
	double phi(double x);

	const int MAX_ITERATION_TIMES_ERROR = 1;
	const double epsilon = 1e-14;
	const double maxIterationTimes = 100;
}
namespace NetownIteration
{
	bool findZeros(double& ans);
	double iterationFunction();
	double function(double x);
	double derivative(double x0, double (*f)(double));
	double phi(double x, int timesOfZeros);
	const int MAX_ITERATION_TIMES_ERROR = 1;
	const int DERIVATIVE_IS_ZERO_ERRO = 2;
	const double epsilon = 0.5e-14;
	const double maxIterationTimes = 100;
}