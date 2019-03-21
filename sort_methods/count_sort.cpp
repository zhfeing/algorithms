#include "count_sort.h"
#define MAX_SIZE 0x5000000
int data[MAX_SIZE];
void countSort(int d[], int len)
{
	int min = d[0];
	int max = d[0];
	for (int *p = d + 1; p < d + len; p++)
	{
		if (*p < min)
			min = *p;
	}
	for (int *p = d + 1; p < d + len; p++)
	{
		if (*p > max)
			max = *p;
	}
	const int valueRank = max - min + 1;
	int *count = new int[valueRank];
	int *temp = new int[len];
	for (int *p = count; p < count + valueRank; p++)
	{
		*p = 0;
	}
	for (int *p = d; p < d + len; p++)
	{
		count[*p - min]++;
	}
	for (int *p = count; p < count + valueRank - 1; p++)
	{
		*(p + 1) += *p;
	}	
	for (int i = len - 1; i > -1; i--)
	{
		temp[count[d[i] - min]-- - 1] = d[i];
	}
	delete[] count;
	for (int i = 0; i < len; i++)
		d[i] = temp[i];
	for (int i = 0; i < len; i++)
	{
		//printf("%d ", temp[i]);
	}
	delete[] temp;
}
int main()
{
	srand(time(0));
	for (int i = 0; i < MAX_SIZE; i++)
	{
		data[i] = rand()%1500000;
	}
	for (int i = 0; i < MAX_SIZE; i++)
	{
		//printf("%d ", data[i]);
	}
	putchar('\n');
	countSort(data, MAX_SIZE);
	for (int i = 0; i < MAX_SIZE; i++)
	{
		//printf("%d ", data[i]);
	}
	return 0;
}