#include<time.h>
#include<stdlib.h>
#define N 100000
void radom(int*A);
void radom(int*A)
{
	srand((unsigned int)time(0));
	int i;
	for (i = 0; i < N; i++)
	{
		A[i] = rand() % 10000;
	}
}