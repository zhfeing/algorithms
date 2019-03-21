#include<stdio.h>
#include<math.h>
double solve(int i, double*a, double x, int n);
int main()
{
	int n;
	printf("enter the max exp(max=200)\n");
	scanf("%d", &n);
	double a[200], x;
	int i;
	for (i = 0; i < 200; i++) a[i] = 0;
	printf("type in the coefficient\n");
	for (i = n; i > -1; i--) 
		scanf("%lf", &a[i]);//enter the coefficient
	printf("enter the 'x0'\n");
	scanf("%lf", &x);
	double slution;
	slution = solve(0, &a[0], x, n);
	printf("%lf\n", slution);
	getchar();
	getchar();
	return 0;
}
double solve(int i, double*a, double x, int n)//an,an-1,x,n
{
	double fx;//contain the return value
	if (i != n)
	{
		fx = *a;
		i++;
		fx += x*solve(i, ++a, x, n);
	}
	else return *a;
	return fx;
}
