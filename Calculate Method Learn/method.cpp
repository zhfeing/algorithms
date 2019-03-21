#include "cMethod.h"

double SimpleLinearIteration::phi(double x)
{
	return pow(1+x,1.0/3);
}
double SimpleLinearIteration::iterationFunction()
{
	double range[2] = { 1, 2 };
	assert(range[0] < range[1]);
	double x0 = range[0] + (range[1] - range[0]) / 2;
	double x1 = phi(x0);
	double error = abs(x1 - x0);
	int i;
	for (i = 0; i < maxIterationTimes && error >= epsilon;i++)
	{
		x0 = phi(x1);
		error = abs(x0 - x1);
		x1 = x0;
	}
	if (i == maxIterationTimes)
		throw MAX_ITERATION_TIMES_ERROR;
	else
	{
		printf("total running times = %d\n", i);
	}
		return x0;
}
bool SimpleLinearIteration::findZeros(double& ans)
{	
	try
	{
		ans = iterationFunction();
	}
	catch (int erro)
	{
		if (erro == MAX_ITERATION_TIMES_ERROR)
			printf("CANNOT FIND ZEROS, ITERATION DOES NOT CONVERGANCE\n");
		return false;
	}
	return true;
}

double NetownIteration::function(double x)
{
	return log(x) - 1;
}
double NetownIteration::derivative(double x0, double(*f)(double))
{
	double detla = x0 / 10000;
	return (f(x0 + detla) - f(x0 - detla)) / 2 / detla;
}
double NetownIteration::phi(double x, int timesOfZeros)
{
	double d = derivative(x, function);
	if (abs(d) < 1e-10)
	{
		throw DERIVATIVE_IS_ZERO_ERRO;
	}
	return x - timesOfZeros*function(x) / d;
}
bool NetownIteration::findZeros(double& ans)
{
	try
	{
		ans = iterationFunction();
	}
	catch (int erro)
	{
		if (erro == MAX_ITERATION_TIMES_ERROR)
			printf("CANNOT FIND ZEROS, ITERATION DOES NOT CONVERGANCE\n");
		return false;
	}
	return true;
}
double NetownIteration::iterationFunction()
{
	const int TIMES_OF_ZEROS = 1;
	
	double range[2] = { 0, 20 };
	assert(range[0] < range[1]);

	double x0 = range[0] + (range[1] - range[0]) / 2;
	double x1 = phi(x0, TIMES_OF_ZEROS);
	double error = abs(x1 - x0);

	int i;
	for (i = 0; i < maxIterationTimes && error >= epsilon; i++)
	{
		try
		{
			x0 = phi(x1, TIMES_OF_ZEROS);
		}
		catch (int erro)
		{
			if (erro == DERIVATIVE_IS_ZERO_ERRO)
			{
				printf("CANNOT FIND ZEROS, DERIVATIVE IS ZERO\n");
				exit(-1);
			}
		}
		error = abs(x0 - x1);
		x1 = x0;
	}
	if (i == maxIterationTimes)
		throw MAX_ITERATION_TIMES_ERROR;
	else
	{
		printf("total running times = %d\n", i);
	}
	return x0;
}