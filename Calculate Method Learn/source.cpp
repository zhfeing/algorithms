#include "cMethod.h"
int main()
{
	double ans;
	/*if(false == SimpleLinearIteration::findZeros(ans))
		return -1;
	printf("WITH SIMPLE LINEAR ITERATION, ANS = %.14lf\n", ans);*/

	if (false == NetownIteration::findZeros(ans))
		return -1;
	printf("WITH NETOWN ITERATION, ANS = %.14lf\n", ans);
	printf("error = %.3e\n", abs(exp(1) - ans));
	return 0;
}