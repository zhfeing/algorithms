#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <assert.h>
#include <algorithm>
int count;
#define HEAP_MAXSIZE 100000
int MaxHeap[HEAP_MAXSIZE + 1];
void maxHeap(int i);
void maxHeap(int i, int heapSize);
void printHeap();
void initHeap();
bool isPowerOfTwo(int a);
inline int parent(int i)
{
	return i >> 1;
}
inline int leftSon(int i)
{
	return i << 1;
}
inline int rightSon(int i)
{
	return (i << 1) + 1;
}
inline void swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}
void setupHeap();
void setupHeap(int heapSize);
void heapSort();
int cmp(const void *a, const void *b)
{
	int aa = *(int*)a;
	int bb = *(int*)b;
	return aa > bb;
}
int main()
{
	initHeap();
	//printHeap();
	//putchar('\n');
	//setupHeap(3);
	//printHeap(); 
	heapSort();
	//for (int i = 1; i < HEAP_MAXSIZE; i++)
	//{
		//printf("%d ", MaxHeap[i]);
	//}
	printf("\nrunning %d\n", count);
}
void initHeap()
{
	srand(time(0));
	for (int i = 1; i < HEAP_MAXSIZE; i++)
	{
		//MaxHeap[i] = rand();
		MaxHeap[i] = i;
	}
}
bool isPowerOfTwo(int a)
{
	if (a < 0)
		a = -a;
	int power = log2((double)a);
	if (a - pow(2.0, power) < 1e-6)
		return true;
	else
		return false;
}
void printHeap()
{
	for (int i = 1; i < HEAP_MAXSIZE; i++)
	{
		printf("%d  ", MaxHeap[i]);
		if (isPowerOfTwo(i + 1))
		{
			putchar('\n');
		}
	}
	putchar('\n');
	putchar('\n');
}
void setupHeap()
{
	for (int i = HEAP_MAXSIZE / 2; i > 0; i--)
	{
		maxHeap(i);
	}
}
void setupHeap(int heapSize)
{
	for (int i = heapSize / 2; i > 0; i--)
	{
		maxHeap(i, heapSize);
	}
}
void maxHeap(int i)
{
	assert(i <= HEAP_MAXSIZE);
	int largest;
	int largestNode;
	int l = leftSon(i);
	int r = rightSon(i);
	if (l <= HEAP_MAXSIZE && MaxHeap[l] > MaxHeap[i])
	{
		largest = MaxHeap[l];
		largestNode = l;
	}
	else
	{
		largest = MaxHeap[i];
		largestNode = i;
	}
	if (r <= HEAP_MAXSIZE && MaxHeap[r] > MaxHeap[largestNode])
	{
		largest = MaxHeap[r];
		largestNode = r;
	}
	if (i == largestNode)
		return;
	swap(MaxHeap + i, MaxHeap + largestNode);
	count++;
	maxHeap(largestNode);
}
void maxHeap(int i, int heapSize)
{
	assert(i <= heapSize);
	int largest;
	int largestNode;
	int l = leftSon(i);
	int r = rightSon(i);
	if (l <= heapSize && MaxHeap[l] > MaxHeap[i])
	{
		largest = MaxHeap[l];
		largestNode = l;
	}
	else
	{
		largest = MaxHeap[i];
		largestNode = i;
	}
	if (r <= heapSize && MaxHeap[r] > MaxHeap[largestNode])
	{
		largest = MaxHeap[r];
		largestNode = r;
	}
	if (i == largestNode)
		return;
	swap(MaxHeap + i, MaxHeap + largestNode);
	count++;
	maxHeap(largestNode, heapSize);
}
void heapSort()
{
	setupHeap(HEAP_MAXSIZE);
	for (int i = HEAP_MAXSIZE - 1; i > 1; )
	{
		swap(MaxHeap + 1, MaxHeap + i);
		count++;
		i--;
		maxHeap(1, i);
	}
}