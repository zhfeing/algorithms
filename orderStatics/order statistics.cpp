#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 50

int findTheKthSmallNumber(int arr[], const int begin, const int end, const int k);
inline void swap(int& a, int& b)
{
	int temp = a;
	a = b;
	b = temp;
}
int main()
{
	int arr[MAX_SIZE];
	for (int i = 0; i < MAX_SIZE; i++)
	{
		arr[i] = rand() % 21;
		printf("%d ", arr[i]);
	}
	putchar('\n');
	int k = 0;
	int res = findTheKthSmallNumber(arr, 0, MAX_SIZE - 1, k);
	printf("The %d small number is %d\n", k + 1, res);
	return 0;
}
int findTheKthSmallNumber(int arr[], const int begin, const int end, const int k)
{
	if (begin == end)
		return arr[begin];
	else if (begin > end)
	{
		printf("wrong");
	}
	int r = rand() % (end - begin + 2) + begin;
	int pivoit = arr[r];
	swap(arr[begin], arr[r]);

	int i, j;
	for (i = begin, j = begin + 1; j <= end; j++)
	{
		
		if (arr[j] <= pivoit)
		{
			swap(arr[j], arr[++i]);
		}
	}
	swap(arr[i], arr[begin]);
	if (arr[i] > arr[k])//the rth small number is bigger then kth number
	{
		findTheKthSmallNumber(arr, begin, i - 1, k);
	}
	else if (arr[i] < arr[k])//the rth small number is smaller than kth number
	{
		findTheKthSmallNumber(arr, i + 1, end, k);
	}
	else
	{
		return arr[i];
	}
}