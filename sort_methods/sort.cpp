#include"sort.h"
int BubbleSort(int*A, int start, int end, char judge)
{
	int*real_start =A + start - 1, *real_end = A + end - 1;//adapt the standard of number group
	int n = end - start + 1;//total number needed sorted
	int*p1, *p2;
	int temp;
	switch (judge)
	{
	case 's':
		for (p1 = real_end; p1 != real_start; p1--)
		{
			for (p2 = real_start; p2 < p1; p2++)
			{
				if (*p2 > *(p2 + 1))
				{
					temp = *(p2 + 1); *(p2 + 1) = *p2; *p2 = temp;
				}
			}
		}
		SORT_ERROR = ALL_RIGHT;
		break;
	case'j':
		for (p1 = real_start; p1 < real_end; p1++)
		{
			for (p2 = p1; p2 < real_end; p2++)
			{
				if (*p2 < *(p2 + 1))
				{
					temp = *(p2 + 1); *(p2 + 1) = *p2; *p2 = temp;
				}
			}
		}
		SORT_ERROR = ALL_RIGHT;
		break;
	default:SORT_ERROR = INPUT_ERROR;
	}
	return SORT_ERROR;
}
int QuickSort(int*A, int start, int end, char judge)
{
	int*real_start = A + start - 1, *real_end = A + end - 1;//adapt the standard of number group
	int n = end - start + 1;//total number needed sorted
	if (n > 1)
	{
		int*p_start = real_start, *p_end = real_end + 1;
		int temp;
		int mid;
		switch (judge)
		{
		case 's':
			while (p_start < p_end)
			{
				for (p_end--; *p_end >= *real_start && p_end > p_start; p_end--);
				for (p_start++; *p_start <= *real_start && p_start < p_end; p_start++);
				if (p_start < p_end)
				{
					temp = *p_end; *p_end = *p_start; *p_start = temp;
				}
				else
				{
					temp = *p_end; *p_end = *real_start; *real_start = temp;
				}
			}
			mid = p_end - A + 1;
			SORT_ERROR = ALL_RIGHT;
			QuickSort(A, start, mid - 1, judge); QuickSort(A, mid + 1, end, judge);
			break;
		case'j':
			while (p_start < p_end)
			{
				for (p_end--; *p_end <= *real_start && p_end > p_start; p_end--);
				for (p_start++; *p_start >= *real_start && p_start < p_end; p_start++);
				if (p_start < p_end)
				{
					temp = *p_end; *p_end = *p_start; *p_start = temp;
				}
				else
				{
					temp = *p_end; *p_end = *real_start; *real_start = temp;
				}
			}
			mid = p_end - A + 1;
			SORT_ERROR = ALL_RIGHT;
			QuickSort(A, start, mid - 1, judge); QuickSort(A, mid + 1, end, judge);
			break;
		default:SORT_ERROR = INPUT_ERROR;
		}
		return SORT_ERROR;
	}
	else return ALL_RIGHT;
}
int InsertionSort(int*A, int start, int end, char judge)
{
	int*real_start = A + start - 1, *real_end = A + end - 1;//adapt the standard of number group
	int n = end - start + 1;//total number needed sorted
	int*p1, *p2;
	int temp;
	switch (judge)
	{
	case 's':
		for (p1 = real_start; p1 < real_end; p1++)
		{
			temp = *(p1 + 1);
			for (p2 = p1; p2 > real_start - 1 && *p2 > temp; p2--)
			{
				*(p2 + 1) = *p2;
			}
			p2++; *p2 = temp;
		}
		SORT_ERROR = ALL_RIGHT;
		break;
	case'j':
		for (p1 = real_start; p1 <= real_end; p1++)
		{
			temp = *(p1 + 1);
			for (p2 = p1; p2 > real_start - 1 && *p2 < temp; p2--)
			{
				*(p2 + 1) = *p2;
			}
			p2++; *p2 = temp;
		}
		SORT_ERROR = ALL_RIGHT;
		break;
	default:SORT_ERROR = INPUT_ERROR;
	}
	return SORT_ERROR;
}
int SeltionSort(int*A, int start, int end, char judge)
{
	int*real_start = A + start - 1, *real_end = A + end - 1;//adapt the standard of number group
	int n = end - start + 1;//total number needed sorted
	int*p1, *p2;
	int temp;
	switch (judge)
	{
	case 's':
		for (p1 = real_start; p1 < real_end; p1++)
		{
			for (p2 = p1; p2 <= real_end; p2++)
			{
				if (*p2 < *p1)
				{
					temp = *p1; *p1 = *p2; *p2 = temp;
				}
			}
		}
		SORT_ERROR = ALL_RIGHT;
		break;
	case 'j':
		for (p1 = real_start; p1 < real_end; p1++)
		{
			for (p2 = p1; p2 <= real_end; p2++)
			{
				if (*p2 > *p1)
				{
					temp = *p1; *p1 = *p2; *p2 = temp;
				}
			}
		}
		SORT_ERROR = ALL_RIGHT;
		break;
	default:SORT_ERROR = INPUT_ERROR;
	}
	return SORT_ERROR;
}
